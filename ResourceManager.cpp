#include "ResourceManager.h"



void ResourceManager::Destroy()
{
	for(std::map<std::string, void*>::iterator it = m_ResDB.begin(); it != m_ResDB.end(); it++) {
		delete (*it).second;
		(*it).second = NULL;
	}
	m_ResDB.clear();
}


void* ResourceManager::LoadResource(RES_TYPE type, const std::string& name)
{
	// La ressource est déja chargée, on ne la recharge pas :
	if(m_ResDB.find(name) != m_ResDB.end())
		return m_ResDB.find(name)->second;

	std::cerr << "Loading resource " << name << std::endl;

	// on charge la ressource
	void* ptr = NULL;
	switch(type) {
	case TEXTURE2D: {
		ptr = new Texture2D();
		((Texture2D*)ptr)->Load(name);
		break;}
	case TEXTURECUBEMAP: {
		ptr = new TextureCubemap();
		((TextureCubemap*)ptr)->Load(name);
		break;}
	case SHADER: {
		ptr = new Shader();
		((Shader*)ptr)->Load(name);
		break;}
	case MESH: {
		ptr = new Mesh();
		((Mesh*)ptr)->Load(name);
		break;}
	}

	if(!ptr) return NULL;

	m_ResDB[name] = ptr;
	return ptr;
}

void* ResourceManager::NewResource(void* data, const std::string& name)
{
	if(!data) return NULL;

	// La ressource est déja chargée, on ne la recharge pas :
	if(m_ResDB.find(name) != m_ResDB.end())
		return m_ResDB.find(name)->second;

	m_ResDB[name] = data;
	return data;
}


