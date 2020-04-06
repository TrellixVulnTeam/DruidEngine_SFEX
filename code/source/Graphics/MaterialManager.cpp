#include "MaterialManager.h"
#include "HashMap.h"
#include "Texture.h"
#include "Material.h"
#include "Shader.h"

namespace DE {

// ---------------------------------------------------------------------------

MaterialManager::MaterialManager() : DE_Class() {
  mTexturesMap = nullptr;
  mMaterialsMap = nullptr;
}

MaterialManager::~MaterialManager() {
  // TODO : remove textures
  // TODO : remove materials
  // TODO : remove MAPs
}

// ---------------------------------------------------------------------------

void MaterialManager::init(){
	TRACE();

  mTexturesMap = Memory::allocate<HashMap<std::string, Texture*>>();
  mTexturesMap->init();

  mMaterialsMap = Memory::allocate<HashMap<std::string, Material*>>();
  mMaterialsMap->init();
}

// ---------------------------------------------------------------------------

Texture* MaterialManager::loadTexture(const std::string& path) {
  Texture* texture = nullptr;

  if(mTexturesMap->contains(path)){
    texture = mTexturesMap->get(path);
  } else {
    texture = Memory::allocate<Texture>();
    texture->init(path);
    mTexturesMap->set(path, texture);
  }

  return texture;
}

// ---------------------------------------------------------------------------

Material* MaterialManager::loadMaterial(const std::string& path) {
  Material* material = nullptr;

  if(mMaterialsMap->contains(path)){
    material = mMaterialsMap->get(path);
  } else {
    material = Memory::allocate<Material>();
    material->init();
    material->setTexture(loadTexture(path));
    material->setShader(Shader::getDefaultShader());
  }

  return material;
}

// ---------------------------------------------------------------------------

} /* namespace DE */
