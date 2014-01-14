#include "Renderer.h"


Renderer::Renderer(EntityPlayer player, std::shared_ptr<Camera> camIn, SDL_Surface ct, std::vector<TypeTile> tileTypes)
{
	cam = camIn;

	modelPlayer = new ModelSquare("../assets/shaders/basic.vert", "../assets/shaders/basic.frag");
	modelOnlinePlayer = new ModelSquare("../assets/shaders/basic.vert", "../assets/shaders/basic.frag");
	modelTile = new ModelSquare("../assets/shaders/tile.vert", "../assets/shaders/tile.frag");
	initShaders();

	glUniform1i(modelTile->getUniform("maxId"), tileTypes.size());
	glUniform1i(modelTile->getUniform("widthPerTexture"), 256);

	texPlayer = pathToOGLTexture(player.getTexture());
	texOnlinePlayer = pathToOGLTexture(player.getTexture());
	texTile = surfaceToOGLTexture(ct);

	glClearColor(1.0, 1.0, 1.0, 1.0);

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	printError("Renderer|Renderer");
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
}

void Renderer::render(std::HashMap<glm::ivec2, std::shared_ptr<Chunk> > chunks, EntityPlayer player, std::vector<std::shared_ptr<PlayerMP> > players)
{
	SDL_GetWindowSize(Graphics::getInstance().getWindow(), &w, &h);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	
	renderTile(chunks, player);
	renderPlayer(player);
	if(player.isOnline())
		renderOnlinePlayers(players, player);

	SDL_GL_SwapWindow(Graphics::getInstance().getWindow());
}

void Renderer::renderTile(std::HashMap<glm::ivec2, std::shared_ptr<Chunk> > chunks, EntityPlayer player)
{
	glUseProgram(modelTile->getProg());

	glm::vec2 playerOffset = glm::vec2(-player.getCenterPosition().x + w/2, -player.getCenterPosition().y + h/2);

	glUniformMatrix4fv(modelTile->getUniform("projMatrix"), 1, GL_FALSE, glm::value_ptr(cam->getOrthoMatrix()));
	//glUniform1i(modelTile->getUniform("texUnit"), 0);
	glBindTexture(GL_TEXTURE_2D, texTile);

	for(auto tile: ChunkUtility::getSurroundingTiles(chunks, Settings::Engine::renderDistance, player))
	{
		if(tile != nullptr)
		{
			glm::mat4 modelMat(1.0);
			modelMat = glm::translate(modelMat, glm::vec3(tile->getPosition()->x*tile->getSize().x + playerOffset.x, tile->getPosition()->y*tile->getSize().y + playerOffset.y, 0.0));
			modelMat = glm::scale(modelMat, glm::vec3(tile->getSize().x, tile->getSize().y, 1.0));
			glUniformMatrix4fv(modelTile->getUniform("modelViewMatrix"), 1, GL_FALSE, glm::value_ptr(modelMat));
			glUniform1i(modelTile->getUniform("textureId"), tile->getTextureId());
			
			glDrawArrays(GL_TRIANGLE_STRIP, 0, modelTile->getNumVertices());
		}
	}
	printError("Renderer|renderTile");
}

void Renderer::renderGrid(EntityPlayer player)
{
	glm::vec2 playerOffset = glm::vec2(-player.getCenterPosition().x + w/2, -player.getCenterPosition().y + h/2);

	//SDL_Renderer* renderer = Graphics::getInstance().getRenderer();

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

	glDrawArrays(GL_TRIANGLE_STRIP, 0, modelPlayer->getNumVertices());
	printError("Renderer|renderPlayer");
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
	
	printError("Renderer|renderOnlinePlayers");
}

GLuint Renderer::pathToOGLTexture(std::string path)
{
	SDL_Surface* tex = IMG_Load(path.c_str());
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

	glTexImage2D(GL_TEXTURE_2D, 0, nbOfColors, tex->w, tex->h, 0, textureFormat, GL_UNSIGNED_BYTE, tex->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	printError("Renderer|surfaceToOGLTexture");
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

	glTexImage2D(GL_TEXTURE_2D, 0, nbOfColors, tex.w, tex.h, 0, textureFormat, GL_UNSIGNED_BYTE, tex.pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	printError("Renderer|surfaceToOGLTexture");
	return texture;
}