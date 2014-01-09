#include "Renderer.h"


Renderer::Renderer(EntityPlayer* player, Camera* camIn)
{
	cam = camIn;

	//progEntity = new ShaderProgram("res/shaders/entity.vert", "res/shaders/entity.frag");
	modelPlayer = new ModelSquare("res/shaders/entity.vert", "res/shaders/entity.frag");

	glUseProgram(modelPlayer->getProg());

	initShaders();

	playerTex = surfaceToOGLTexture(TextureManager::getInstance().getSurface("mario"));
	//glUniform1i(progEntity->getUniform("texUnit"), 0);
	//playerTex = surfaceToOGLTexture(player->getModel()->getSurface());
	//glUniform1i(glGetUniformLocation(entityProg, "texUnit"), 0);

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
	modelPlayer->addAttrib(BUFFTYPE::VERTEX, "inPosition");
	modelPlayer->addAttrib(BUFFTYPE::TEXCOORD, "inTexCoord");

	modelPlayer->addUniform("projMatrix");
	modelPlayer->addUniform("modelViewMatrix");
	modelPlayer->addUniform("texUnit");
}

void Renderer::render(std::HashMap<glm::ivec2, Chunk*> chunks, EntityPlayer* player, std::vector<PlayerMP*> players)
{
	SDL_GetWindowSize(Graphics::getInstance().getWindow(), &w, &h);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	
	renderEntity(player, players);
	//renderGrid(player);
	//renderTile(chunks, player);

	SDL_GL_SwapWindow(Graphics::getInstance().getWindow());
}

void Renderer::renderTile(std::HashMap<glm::ivec2, Chunk*> chunks, EntityPlayer* player)
{
	/*std::vector<Tile*> v = ChunkUtility::getSurroundingTiles(chunks, RenderDistance, player);

	glm::vec2 playerOffset = glm::vec2(-player->getCenterPosition().x + w/2, -player->getCenterPosition().y + h/2);

	for(Tile* tile: v)
	{
		if(tile != nullptr)
		{
			SDL_Texture* tex = tile->getTexture();
			dst.x = tile->getPosition()->x*dst.w + playerOffset.x;
			dst.y = tile->getPosition()->y*dst.h + playerOffset.y;

			glm::vec3* tmpColorMod = tile->getColorMod();
			SDL_SetTextureColorMod(tex, tmpColorMod->x, tmpColorMod->y, tmpColorMod->z);

			renderTexture(tex, dst);
		}
	}*/
}

void Renderer::renderGrid(EntityPlayer* player)
{
	glm::vec2 playerOffset = glm::vec2(-player->getCenterPosition().x + w/2, -player->getCenterPosition().y + h/2);

	//SDL_Renderer* renderer = Graphics::getInstance().getRenderer();

	std::vector<glm::vec2> points;

	for(int x = player->getPosition()->x-w; x < player->getPosition()->x+w; x+=TileWidth)
	{
		int tmpX = x-(x%TileWidth);
		

		/*SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xff);
		if(tmpX%(TileAmount*TileWidth) == 0)
			SDL_SetRenderDrawColor(renderer, 0xff, 0x0, 0x0, 0xff);*/	

		//SDL_RenderDrawLine(renderer, tmpX+playerOffset.x, 0, tmpX+playerOffset.x, h);
		
		for(int y = player->getPosition()->y-h; y < player->getPosition()->y+h; y+=TileHeight)
		{

			int tmpY = y-(y%TileHeight);
			
			/*SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xff);
			if(tmpY%(TileAmount*TileHeight) == 0)
				SDL_SetRenderDrawColor(renderer, 0xff, 0x0, 0x0, 0xff);	*/

			//SDL_RenderDrawLine(renderer, 0, tmpY+playerOffset.y, w, tmpY+playerOffset.y);
			
			points.push_back(glm::vec2(tmpX+playerOffset.x, tmpY+playerOffset.y));

			std::cout << "X: " << tmpX+playerOffset.x << " Y: " << tmpY+playerOffset.y << std::endl;
		}
	}


}

void Renderer::renderEntity(EntityPlayer* player, std::vector<PlayerMP*> players)
{
	glUseProgram(modelPlayer->getProg());
	
	glm::mat4 modelMat(1.0);
	modelMat = glm::translate(modelMat, glm::vec3(w/2 - player->getModel()->getWidth()/2, h/2 + player->getModel()->getHeight()/2 + player->getBB()->getHeight()/2, 0.0));
	modelMat = glm::scale(modelMat, glm::vec3(player->getModel()->getWidth(), player->getModel()->getHeight(), 1.0));
	glUniformMatrix4fv(modelPlayer->getUniform("modelViewMatrix"), 1, GL_FALSE, glm::value_ptr(modelMat));
	glUniformMatrix4fv(modelPlayer->getUniform("projMatrix"), 1, GL_FALSE, glm::value_ptr(cam->getOrthoMatrix()));
	
	glUniform1i(modelPlayer->getUniform("texUnit"), 0);
	glBindTexture(GL_TEXTURE_2D, playerTex);
	glBindVertexArray(modelPlayer->getVAO());

	glDrawArrays(GL_TRIANGLE_STRIP, 0, modelPlayer->getNumVertices());
	printError("Renderer|renderEntity");
}

GLuint Renderer::surfaceToOGLTexture(SDL_Surface* tex)
{
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