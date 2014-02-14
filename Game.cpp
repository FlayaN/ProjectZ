#include "Game.h"

Game::Game(std::shared_ptr<Json> jsonIn, std::string ip, std::shared_ptr<Graphic> graphicIn) : running(true), json(jsonIn)
{
	//music = Mix_LoadWAV("../assets/music/CSLIVE.wav");

	PerlinNoise::getInstance().SetValues(0.25, 6.0, (double)json->getTileTypes().size(), 1, 1337);
	SimplexNoise::init();

    graphic = graphicIn;
	player = std::make_shared<EntityPlayer>(json->getPlayerType());

	for(int i = 0; i < json->getInventoryTypes().size(); i++)
	{
		if(json->getInventoryTypes()[i]->name == json->getPlayerType().inv)
			player->setInventory(json->getInventoryTypes()[i]);
	}

	cam = std::make_shared<Camera>(player);
	renderer = std::unique_ptr<Renderer>(new Renderer(graphic, *player, cam, json->getTileTexture(), json->getTileTypes(), json->getItemTexture(), json->getItemTypes().size()));

	net = std::make_shared<Network>(ip.c_str());

	online = net->getSuccess();
	keyFocus = false;

	chat = std::make_shared<Chat>(10);

	tmpTime = 0;
	newState = false;
	state = STATE::GAME;
}

Game::~Game(void)
{
	chunks.clear();
	players.clear();
	cam.reset();
	player.reset();
	chat.reset();
	json.reset();
	renderer.reset();
}

void Game::onEvent(SDL_Event* ev, const Uint8* keyStates)
{
	switch (ev->type)
	{
		case SDL_QUIT:
			running = false;
			break;
			
		case SDL_KEYDOWN:
		{
			if(ev->key.keysym.sym == SDLK_ESCAPE)
			{
				newState = true;
				state = STATE::MAINMENU;
			}
			else if(ev->key.keysym.sym == SDLK_RETURN)
			{
				if(online)
				{
					if(!keyFocus)
					{
						keyFocus = true;
						chat->setOpen(true);
						SDL_StartTextInput();
					}
					else
					{
						keyFocus = false;
						chat->setOpen(false);
						SDL_StopTextInput();

						if(chat->getCurrText() != "")
						{
							net->sendMessage(*player, TimeChat(chat->getCurrText(), SDL_GetTicks()));
							chat->setCurrText("");
						}
					}
				}
			}
			break;
		}
	}
	if(keyFocus)
		chat->handleKeyInput(ev, keyStates);
	else
		player->onEvent(ev);
}

void Game::update(float delta, const Uint8* keyStates)
{
	//logic
	ChunkUtility::generateSurroundingChunk(chunks, Settings::Engine::chunkDistance, *player, json->getTileTypes(), json->getItemTypes());
	collision();
	if(!keyFocus)
		player->update(delta, keyStates);
	else
		player->updateNoKey(delta);

	if(online)
	{
		for(auto p : players)
		{
			p->update();
		}
	}

	//network
	if(online)
	{
		tmpTime += delta * 1000.0f;//(currTime - oldTime);
		if(tmpTime >= 50) //How often to send data to the server in ms (50 = 20times/second)
		{
			net->send(*player, SDL_GetTicks());
			tmpTime = 0;
		}
		net->recv(chunks, players, player, SDL_GetTicks(), chat);
	}
	if(player->getDropItem())
	{
		if(online)
			net->placeItem(player->getDroppedItemStack());
		else
			chunks[Utility::inChunkCoord(player->getDroppedItemStack()->getPosition())]->addGroundItem(player->getDroppedItemStack());
		player->setDropItem(false);
	}
}

void Game::render()
{
	renderer->render(chunks, *player, players, *chat);
}

bool Game::isRunning(void)
{
	return running;
}

void Game::collision(void)
{
	for(auto tile: ChunkUtility::getSurroundingTiles(chunks, Settings::Engine::collisionDistance, *player))
    {
		if(tile != nullptr)
		{
			glm::ivec2 tileCoord = tile->getPosition();
			glm::ivec2 playerInTileCoord = Utility::inTileCoord(player->getCenterPosition());

			if(playerInTileCoord == tileCoord)
			{
				player->setFriction(tile->getFriction());
			}
		}
	}

	std::vector<std::shared_ptr<TypeItem> > tmpItemTypes = json->getItemTypes();

	glm::ivec2 centerPosInChunk = Utility::inChunkCoord(player->getCenterPosition());

	for(int x = centerPosInChunk.x - 1; x <= centerPosInChunk.x + 1; x++)
	{
		for(int y = centerPosInChunk.y - 1; y <= centerPosInChunk.y + 1; y++)
		{
			std::shared_ptr<Chunk> tmpChunk = chunks[glm::ivec2(x, y)];
			
			if(tmpChunk != nullptr)
			{
				std::vector<std::shared_ptr<GroundItemStack> > tmpGroundItemStack = tmpChunk->getGroundItemStacks();
				
				for(int i = 0; i < tmpGroundItemStack.size(); i++)
				{
					glm::vec2 playerPos = player->getCenterPosition();
					glm::vec2 itemPos = tmpGroundItemStack[i]->getPosition();
					glm::ivec2 chunkPos = Utility::inChunkCoord(itemPos);

					if(	playerPos.x > (itemPos.x - 100) && playerPos.x < (itemPos.x + 100) && playerPos.y > (itemPos.y - 100) && playerPos.y < (itemPos.y + 100))
					{
						int tmpId = tmpGroundItemStack[i]->getId();
						int tmpAmount = tmpGroundItemStack[i]->getAmount();
						glm::vec2 tmpPos = tmpGroundItemStack[i]->getPosition();

						std::shared_ptr<Item> tmpItem = std::make_shared<Item>(tmpItemTypes[tmpId]->name, tmpItemTypes[tmpId]->stackSize, tmpItemTypes[tmpId]->id);
						std::shared_ptr<ItemStack> tmpItemStack = std::make_shared<ItemStack>(tmpItem);
						for(int j = 0; j < tmpAmount; j++)
						{
							tmpItemStack->increaseStack();
						}

						if(player->getInventory()->addItemStack(tmpItemStack))
						{
							if(online)
								net->pickupItem(tmpGroundItemStack[i]);
							tmpChunk->removeGroundItem(tmpId, tmpPos, tmpAmount);
						}
					}
				}
			}
		}
	}
}

bool Game::hasNewState(void)
{
	return newState;
}
STATE Game::requestStateChange(void)
{
	return state;
}
