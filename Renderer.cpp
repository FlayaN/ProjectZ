#include "Renderer.h"


Renderer::Renderer(EntityPlayer player, std::shared_ptr<Camera> camIn, SDL_Surface tileTexture, std::vector<TypeTile> tileTypes, SDL_Surface itemTexture, int itemCount)
{
	cam = camIn;

	modelPlayer = new ModelSquare("assets/shaders/basic.vert", "assets/shaders/basic.frag");
	modelOnlinePlayer = new ModelSquare("assets/shaders/basic.vert", "assets/shaders/basic.frag");
	modelTile = new ModelSquare("assets/shaders/tile.vert", "assets/shaders/tile.frag");
	modelItem = new ModelSquare("assets/shaders/item.vert", "assets/shaders/item.frag");
	modelGui = new ModelSquare("assets/shaders/basic.vert", "assets/shaders/basic.frag");
	initShaders();

	glUseProgram(modelTile->getProg());
	glUniform1i(modelTile->getUniform("maxId"), tileTypes.size());
	glUniform1i(modelTile->getUniform("widthPerTexture"), 256);

	glUseProgram(modelItem->getProg());
	glUniform1i(modelItem->getUniform("maxId"), itemCount);
	glUniform1i(modelItem->getUniform("widthPerTexture"), 32);

	texPlayer = pathToOGLTexture(player.getTexture());
	texOnlinePlayer = pathToOGLTexture(player.getTexture());

	texGui = pathToOGLTexture("assets/images/slot.png");
	texChat = pathToOGLTexture("assets/images/chat.png");

	texTile = surfaceToOGLTexture(tileTexture);
	texItem = surfaceToOGLTexture(itemTexture);

	sfMakeRasterFont();

	sfSetRasterSize(Settings::Graphics::screenWidth, Settings::Graphics::screenHeight);

	glClearColor(1.0, 1.0, 1.0, 1.0);

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

#if DEBUG
	printError("Renderer|Renderer");
#endif
}

Renderer::~Renderer(void) 
{

}

void Renderer::initShaders(void)
{
	//------------------------------PLAYER BUFFER INITIALIZATION----------------------------//
	modelPlayer->addAttrib(BUFFTYPE::VERTEX, "inPosition");
	modelPlayer->addAttrib(BUFFTYPE::TEXCOORD, "inTexCoord");

	modelPlayer->addUniform("projMatrix");
	modelPlayer->addUniform("modelViewMatrix");
	modelPlayer->addUniform("texUnit");

	//---------------------------ONLINE PLAYERS BUFFER INITIALIZATION-----------------------//
	modelOnlinePlayer->addAttrib(BUFFTYPE::VERTEX, "inPosition");
	modelOnlinePlayer->addAttrib(BUFFTYPE::TEXCOORD, "inTexCoord");

	modelOnlinePlayer->addUniform("projMatrix");
	modelOnlinePlayer->addUniform("modelViewMatrix");
	modelOnlinePlayer->addUniform("texUnit");

	//------------------------------TILE BUFFER INITIALIZATION-----------------------------//
	modelTile->addAttrib(BUFFTYPE::VERTEX, "inPosition");
	modelTile->addAttrib(BUFFTYPE::TEXCOORD, "inTexCoord");

	modelTile->addUniform("projMatrix");
	modelTile->addUniform("modelViewMatrix");
	modelTile->addUniform("texUnit");
	modelTile->addUniform("textureId");
	modelTile->addUniform("maxId");
	modelTile->addUniform("widthPerTexture");

	//------------------------------ITEM BUFFER INITIALIZATION-----------------------------//
	modelItem->addAttrib(BUFFTYPE::VERTEX, "inPosition");
	modelItem->addAttrib(BUFFTYPE::TEXCOORD, "inTexCoord");

	modelItem->addUniform("projMatrix");
	modelItem->addUniform("modelViewMatrix");
	modelItem->addUniform("texUnit");
	modelItem->addUniform("textureId");
	modelItem->addUniform("maxId");
	modelItem->addUniform("widthPerTexture");

	//------------------------------GUI BUFFER INITIALIZATION-----------------------------//
	modelGui->addAttrib(BUFFTYPE::VERTEX, "inPosition");
	modelGui->addAttrib(BUFFTYPE::TEXCOORD, "inTexCoord");

	modelGui->addUniform("projMatrix");
	modelGui->addUniform("modelViewMatrix");
	modelGui->addUniform("texUnit");
}

void Renderer::render(std::HashMap<glm::ivec2, std::shared_ptr<Chunk> > chunks, EntityPlayer player, std::vector<std::shared_ptr<PlayerMP> > players, Chat chat)
{
	SDL_GetWindowSize(Graphics::getInstance().getWindow(), &w, &h);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	
	renderTile(chunks, player);
	renderPlayer(player);
	if(player.isOnline())
		renderOnlinePlayers(players, player);

	renderItem(chunks, player);
	renderGui(player);

	if(chat.isOpen())
		renderChat(chat);
	else
		renderTimedChat(chat);

	sprintf(buff, "X %0.1f", player.getPosition().x);
	sfDrawString(10, 10, buff);
	sprintf(buff, "Y %0.1f", player.getPosition().y);
	sfDrawString(10, 30, buff);

	SDL_GL_SwapWindow(Graphics::getInstance().getWindow());
}

void Renderer::renderItem(std::HashMap<glm::ivec2, std::shared_ptr<Chunk> > chunks, EntityPlayer player)
{
	glUseProgram(modelItem->getProg());

	glm::vec2 playerOffset = glm::vec2(-player.getCenterPosition().x + w/2, -player.getCenterPosition().y + h/2);

	glUniformMatrix4fv(modelItem->getUniform("projMatrix"), 1, GL_FALSE, glm::value_ptr(cam->getOrthoMatrix()));
	glBindTexture(GL_TEXTURE_2D, texItem);

	for(auto item: ChunkUtility::getSurroundingItems(chunks, player))
	{
		if(item != nullptr)
		{
			glm::mat4 modelMat(1.0);
			modelMat = glm::translate(modelMat, glm::vec3(item->getPosition().x + playerOffset.x, item->getPosition().y + playerOffset.y, -0.5));
			//sfDrawString(item->getPosition().x*Settings::Tile::width + playerOffset.x - (item->getName().length()/2)*6, (Settings::Graphics::screenHeight - (item->getPosition().y*Settings::Tile::height + playerOffset.y + 34)), &item->getName()[0]);
			modelMat = glm::scale(modelMat, glm::vec3(32, 32, 1.0));
			glUniformMatrix4fv(modelItem->getUniform("modelViewMatrix"), 1, GL_FALSE, glm::value_ptr(modelMat));
			glUniform1i(modelItem->getUniform("textureId"), item->getId());
			
			glBindVertexArray(modelItem->getVAO());

			glDrawArrays(GL_TRIANGLE_STRIP, 0, modelItem->getNumVertices());
		}
	}
#if DEBUG
	printError("Renderer|renderItem");
#endif
}

void Renderer::renderTile(std::HashMap<glm::ivec2, std::shared_ptr<Chunk> > chunks, EntityPlayer player)
{
	glUseProgram(modelTile->getProg());

	glm::vec2 playerOffset = glm::vec2(-player.getCenterPosition().x + w/2, -player.getCenterPosition().y + h/2);

	glUniformMatrix4fv(modelTile->getUniform("projMatrix"), 1, GL_FALSE, glm::value_ptr(cam->getOrthoMatrix()));
	glUniform1i(modelTile->getUniform("texUnit"), 0);
	glBindTexture(GL_TEXTURE_2D, texTile);

	for(auto tile: ChunkUtility::getSurroundingTiles(chunks, Settings::Engine::renderDistance, player))
	{
		if(tile != nullptr)
		{
			glm::mat4 modelMat(1.0);
			modelMat = glm::translate(modelMat, glm::vec3(tile->getPosition().x*tile->getSize().x + playerOffset.x, tile->getPosition().y*tile->getSize().y + playerOffset.y, -1.0));
			modelMat = glm::scale(modelMat, glm::vec3(tile->getSize().x, tile->getSize().y, 1.0));
			glUniformMatrix4fv(modelTile->getUniform("modelViewMatrix"), 1, GL_FALSE, glm::value_ptr(modelMat));
			glUniform1i(modelTile->getUniform("textureId"), tile->getTextureId());
			
			glBindVertexArray(modelTile->getVAO());

			glDrawArrays(GL_TRIANGLE_STRIP, 0, modelTile->getNumVertices());
		}
	}
#if DEBUG
	printError("Renderer|renderTile");
#endif
}

void Renderer::renderGrid(EntityPlayer player)
{
	glm::vec2 playerOffset = glm::vec2(-player.getCenterPosition().x + w/2, -player.getCenterPosition().y + h/2);

	std::vector<glm::vec2> points;

	for(int x = player.getPosition().x-w; x < player.getPosition().x+w; x+=Settings::Tile::width)
	{
		int tmpX = x-(x%Settings::Tile::width);
		

		/*SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xff);
		if(tmpX%(TileAmount*TileWidth) == 0)
			SDL_SetRenderDrawColor(renderer, 0xff, 0x0, 0x0, 0xff);*/	

		//SDL_RenderDrawLine(renderer, tmpX+playerOffset.x, 0, tmpX+playerOffset.x, h);
		
		for(int y = player.getPosition().y-h; y < player.getPosition().y+h; y+=Settings::Tile::height)
		{

			int tmpY = y-(y%Settings::Tile::height);
			
			/*SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xff);
			if(tmpY%(TileAmount*TileHeight) == 0)
				SDL_SetRenderDrawColor(renderer, 0xff, 0x0, 0x0, 0xff);	*/

			//SDL_RenderDrawLine(renderer, 0, tmpY+playerOffset.y, w, tmpY+playerOffset.y);
			
			points.push_back(glm::vec2(tmpX+playerOffset.x, tmpY+playerOffset.y));

			std::cout << "X: " << tmpX+playerOffset.x << " Y: " << tmpY+playerOffset.y << std::endl;
		}
	}


}

void Renderer::renderPlayer(EntityPlayer player)
{
	glUseProgram(modelPlayer->getProg());
	
	glm::mat4 modelMat(1.0);
	modelMat = glm::translate(modelMat, glm::vec3(w/2 - player.getSize().x/2, h/2 - player.getBB()->getHeight()/2, 0.0));
	modelMat = glm::scale(modelMat, glm::vec3(player.getSize().x, player.getSize().y, 1.0));
	glUniformMatrix4fv(modelPlayer->getUniform("modelViewMatrix"), 1, GL_FALSE, glm::value_ptr(modelMat));
	glUniformMatrix4fv(modelPlayer->getUniform("projMatrix"), 1, GL_FALSE, glm::value_ptr(cam->getOrthoMatrix()));
	
	//glUniform1i(modelPlayer->getUniform("texUnit"), 0);
	glBindTexture(GL_TEXTURE_2D, texPlayer);

	glBindVertexArray(modelPlayer->getVAO());

	glDrawArrays(GL_TRIANGLE_STRIP, 0, modelPlayer->getNumVertices());
#if DEBUG
	printError("Renderer|renderPlayer");
#endif
}

void Renderer::renderOnlinePlayers(std::vector<std::shared_ptr<PlayerMP> > players, EntityPlayer player)
{
	glUseProgram(modelOnlinePlayer->getProg());
	glm::vec2 playerOffset = glm::vec2(-player.getCenterPosition().x + w/2, -player.getCenterPosition().y + h/2);

	glUniformMatrix4fv(modelOnlinePlayer->getUniform("projMatrix"), 1, GL_FALSE, glm::value_ptr(cam->getOrthoMatrix()));
	glUniform1i(modelOnlinePlayer->getUniform("texUnit"), 0);
	glBindTexture(GL_TEXTURE_2D, texOnlinePlayer);

	for (auto p : players)
	{
		glm::mat4 modelMat(1.0);
		modelMat = glm::translate(modelMat, glm::vec3(p->getPosition().x + playerOffset.x, p->getPosition().y + playerOffset.y, 0.0));
		modelMat = glm::scale(modelMat, glm::vec3(p->getSize().x, p->getSize().y, 1.0));
		glUniformMatrix4fv(modelOnlinePlayer->getUniform("modelViewMatrix"), 1, GL_FALSE, glm::value_ptr(modelMat));
		
		glDrawArrays(GL_TRIANGLE_STRIP, 0, modelOnlinePlayer->getNumVertices());
	}
#if DEBUG
	printError("Renderer|renderOnlinePlayers");
#endif
}

void Renderer::renderGui(EntityPlayer player)
{
	if(player.hasInventoryOpen())
	{
		std::shared_ptr<Inventory> tmpInv = player.getInventory();


		std::vector<std::shared_ptr<ItemStack> > tmpItems = tmpInv->getItems();
		glm::ivec2 invPos = tmpInv->getPosition();

		
		//RENDER BG
		glUseProgram(modelGui->getProg());
		glUniformMatrix4fv(modelGui->getUniform("projMatrix"), 1, GL_FALSE, glm::value_ptr(cam->getOrthoMatrix()));
		glBindTexture(GL_TEXTURE_2D, texGui);

		for(int i = 0; i < tmpItems.size(); i++)
		{
			glm::mat4 modelMat(1.0);
			modelMat = glm::translate(modelMat, glm::vec3(invPos.x + (i%9)*34, invPos.y + (i/9)*34, 0.0));
			modelMat = glm::scale(modelMat, glm::vec3(34, 34, 1.0));
			glUniformMatrix4fv(modelGui->getUniform("modelViewMatrix"), 1, GL_FALSE, glm::value_ptr(modelMat));
			glBindVertexArray(modelGui->getVAO());

			glDrawArrays(GL_TRIANGLE_STRIP, 0, modelGui->getNumVertices());
		}
		//RENDER FG
		glUseProgram(modelItem->getProg());
		glUniformMatrix4fv(modelItem->getUniform("projMatrix"), 1, GL_FALSE, glm::value_ptr(cam->getOrthoMatrix()));
		glBindTexture(GL_TEXTURE_2D, texItem);

		for(int i = 0; i < tmpItems.size(); i++)
		{
			if(tmpItems.at(i) != nullptr)
			{
				glm::mat4 modelMat(1.0);
				modelMat = glm::translate(modelMat, glm::vec3(invPos.x + (i%9)*34, invPos.y + (i/9)*34, 0.0));
				//sfDrawString(item->getPosition().x*Settings::Tile::width + playerOffset.x - (item->getName().length()/2)*6, (Settings::Graphics::screenHeight - (item->getPosition().y*Settings::Tile::height + playerOffset.y + 34)), &item->getName()[0]);
				modelMat = glm::scale(modelMat, glm::vec3(32, 32, 1.0));
				glUniformMatrix4fv(modelItem->getUniform("modelViewMatrix"), 1, GL_FALSE, glm::value_ptr(modelMat));
				glUniform1i(modelItem->getUniform("textureId"), tmpItems.at(i)->getItem()->getId());
				
				glBindVertexArray(modelItem->getVAO());

				glDrawArrays(GL_TRIANGLE_STRIP, 0, modelItem->getNumVertices());
				sprintf(buff, "%d", tmpItems.at(i)->getCurrSize());
				sfDrawString(invPos.x + (i%9)*34, (Settings::Graphics::screenHeight - (invPos.y + (i/9)*34)), buff);
			}
		}

		if(player.isDraggingItem())
		{
			std::shared_ptr<MouseItem> tmpMouseItem = player.getMouseItem();
			glm::vec2 tmpPos = tmpMouseItem->getPosition();

			glm::mat4 modelMat(1.0);
			modelMat = glm::translate(modelMat, glm::vec3(tmpPos.x, tmpPos.y, 0.0));
			//sfDrawString(item->getPosition().x*Settings::Tile::width + playerOffset.x - (item->getName().length()/2)*6, (Settings::Graphics::screenHeight - (item->getPosition().y*Settings::Tile::height + playerOffset.y + 34)), &item->getName()[0]);
			modelMat = glm::scale(modelMat, glm::vec3(32, 32, 1.0));
			glUniformMatrix4fv(modelItem->getUniform("modelViewMatrix"), 1, GL_FALSE, glm::value_ptr(modelMat));
			glUniform1i(modelItem->getUniform("textureId"), tmpMouseItem->getCurrItemStack()->getItem()->getId());
			
			glBindVertexArray(modelItem->getVAO());

			glDrawArrays(GL_TRIANGLE_STRIP, 0, modelItem->getNumVertices());
			sprintf(buff, "%d", tmpMouseItem->getCurrItemStack()->getCurrSize());
			sfDrawString(tmpPos.x, Settings::Graphics::screenHeight - tmpPos.y, buff);
		}
	}
#if DEBUG
	printError("Renderer|renderGui");
#endif
}

void Renderer::renderChat(Chat chat)
{
	//Render bg
	glUseProgram(modelGui->getProg());
	glUniformMatrix4fv(modelGui->getUniform("projMatrix"), 1, GL_FALSE, glm::value_ptr(cam->getOrthoMatrix()));
	glBindTexture(GL_TEXTURE_2D, texChat);

	glm::mat4 modelMat(1.0);
	modelMat = glm::translate(modelMat, glm::vec3(0, 4, 0.0));
	modelMat = glm::scale(modelMat, glm::vec3(256, 19, 1.0));
	glUniformMatrix4fv(modelGui->getUniform("modelViewMatrix"), 1, GL_FALSE, glm::value_ptr(modelMat));
	glBindVertexArray(modelGui->getVAO());

	glDrawArrays(GL_TRIANGLE_STRIP, 0, modelGui->getNumVertices());


	//Render text
	strcpy(buff, chat.getCurrText().c_str());
	sfDrawString(10, Settings::Graphics::screenHeight - 10, buff);
	std::vector<std::shared_ptr<TimeChat> > chatLog = chat.getChatLog();

	int amountOfChat = chatLog.size();

	if(amountOfChat <= 10)
	{
		for(int i = 0; i < amountOfChat; i++)
		{
			strcpy(buff, chatLog[i]->chat.c_str());
			sfDrawString(10, Settings::Graphics::screenHeight - (15*((chatLog.size()-i)+1)), buff);
		}
	}
	else
	{
		for(int i = amountOfChat-10; i < amountOfChat; i++)
		{
			strcpy(buff, chatLog[i]->chat.c_str());
			sfDrawString(10, Settings::Graphics::screenHeight - (15*((chatLog.size()-i)+1)), buff);
		}
	}
#if DEBUG
	printError("Renderer|renderChat");
#endif
}

void Renderer::renderTimedChat(Chat chat)
{
	strcpy(buff, chat.getCurrText().c_str());
	sfDrawString(10, Settings::Graphics::screenHeight - 10, buff);
	std::vector<std::shared_ptr<TimeChat> > chatLog = chat.getChatLog();

	int amountOfChat = chatLog.size();

	if(amountOfChat <= 10)
	{
		for(int i = 0; i < amountOfChat; i++)
		{
			if((SDL_GetTicks() - chatLog[i]->time) < 5000)
			{
				strcpy(buff, chatLog[i]->chat.c_str());
				sfDrawString(10, Settings::Graphics::screenHeight - (15*((chatLog.size()-i)+1)), buff);
			}
		}
	}
	else
	{
		for(int i = amountOfChat-10; i < amountOfChat; i++)
		{
			if((SDL_GetTicks() - chatLog[i]->time) < 5000)
			{
				strcpy(buff, chatLog[i]->chat.c_str());
				sfDrawString(10, Settings::Graphics::screenHeight - (15*((chatLog.size()-i)+1)), buff);
			}
		}
	}
#if DEBUG
	printError("Renderer|renderTimedChat");
#endif
}

GLuint Renderer::pathToOGLTexture(std::string path)
{
    path = Utility::getBasePath() + path;
	SDL_Surface* tex = IMG_Load(path.c_str());
    if(tex == nullptr)
        std::cout << "ERROR: " << std::endl;
	GLuint texture;
	GLint nbOfColors;
	GLenum textureFormat = 0;

	nbOfColors = tex->format->BytesPerPixel;

	switch(nbOfColors)
	{
		case 1:
			textureFormat = GL_ALPHA;
			break;
		case 3: //no alpha
			if(tex->format->Rmask == 0x000000ff)
				textureFormat = GL_RGB;
			else
				textureFormat = GL_BGR;
			break;
		case 4: //contains alpha
			if(tex->format->Rmask == 0x000000ff)
				textureFormat = GL_RGBA;
			else
				textureFormat = GL_BGRA;
			break;
		default:
			break;
	}

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
		
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex->w, tex->h, 0, textureFormat, GL_UNSIGNED_BYTE, tex->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

#if DEBUG
	printError("Renderer|pathToOGLTexture");
#endif

	return texture;
}

GLuint Renderer::surfaceToOGLTexture(SDL_Surface tex)
{
	GLuint texture;
	GLint nbOfColors;
	GLenum textureFormat = 0;

	nbOfColors = tex.format->BytesPerPixel;

	switch(nbOfColors)
	{
		case 1:
			textureFormat = GL_ALPHA;
			break;
		case 3: //no alpha
			if(tex.format->Rmask == 0x000000ff)
				textureFormat = GL_RGB;
			else
				textureFormat = GL_BGR;
			break;
		case 4: //contains alpha
			if(tex.format->Rmask == 0x000000ff)
				textureFormat = GL_RGBA;
			else
				textureFormat = GL_BGRA;
			break;
		default:
			break;
	}
    
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
	glTexImage2D(GL_TEXTURE_2D, 0, textureFormat, tex.w, tex.h, 0, textureFormat, GL_UNSIGNED_BYTE, tex.pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

#if DEBUG
	printError("Renderer|surfaceToOGLTexture");
#endif

	return texture;
}