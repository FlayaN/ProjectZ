#ifndef SERVERLIST_H
#define SERVERLIST_H

#include <regex>

#include <curl/curl.h>
#include "lib/rapidjson/document.h"
#include "lib/rapidjson/filestream.h"
#include <enet/enet.h>

#include "BaseWindow.h"
#include "GuiServerList.h"

class ServerList : public BaseWindow
{
public:
	ServerList(std::shared_ptr<Graphic>);
	void renderBody(void);
	void onEvent(SDL_Event*, const Uint8*);
	void update(float, const Uint8*);
	std::string getIp(void);
private:
	void loadServerList(void);
	std::vector<GuiServerList> serverList;
	std::string ip;
	std::string yourIp;
};

#endif