#include "gameengine.h"
#include "player.h"

GameEngine::GameEngine(Ogre::SceneManager *manager, Gorilla::Screen *screen)
{
	mScreen = screen;
	mInitialized = false;
	mSceneMgr = manager;
	mMap = NULL;
}

GameEngine::~GameEngine()
{
	delete mPlayer;

}

void GameEngine::init()
{
	mPlayer = new Player(this);
	mPlayer->getPosition() = Ogre::Vector3(5*WORLDSCALE,5*WORLDSCALE,0);
	Item *item = new Item(this);
	item->getPosition() = Ogre::Vector3(5*WORLDSCALE,5*WORLDSCALE,0);
	mItems.push_back(item);
	addBillboardItemToWorld(*mPlayer, "playerNode");
	addBillboardItemToWorld(*item, "itemNode");
	mMap = new GameMap(256, 256, DUNGEON, mSceneMgr, &mTileSetMgr);
	mInitialized = true;
	mLayer = mScreen->createLayer(0);
	mBackgroundRect = mLayer->createRectangle(0,mScreen->getHeight()-150, 200, 150);
	mHealthBarRect = mLayer->createRectangle(20, mScreen->getHeight()-130, 160, 20);
	updateHUD();
}

void GameEngine::updateHUD() {
	float prop = double(mPlayer->getHealth())/mPlayer->getMaxHealth();
	mHealthBarRect->background_colour(Gorilla::rgb(240, 70-prop/2, 70-prop/2));
	mHealthBarRect->width(prop*160);
	mBackgroundRect->background_gradient(Gorilla::Gradient_Diagonal, Gorilla::rgb(0,0,0), Gorilla::rgb(100,100*prop,100*prop));
}

void GameEngine::addBillboardItemToWorld(BillboardItem &item, Ogre::String id)
{
	Ogre::BillboardSet *set = mSceneMgr->createBillboardSet();
	set->setDefaultDimensions(WORLDSCALE, WORLDSCALE);
	set->setMaterialName(item.getResID());
	set->setBounds(Ogre::AxisAlignedBox::BOX_INFINITE, 0);
	item.setBillboard(set->createBillboard(0, 0, 0));
	item.getSceneName() = id;
	Ogre::SceneNode *node;
	node = mSceneMgr->getRootSceneNode()->createChildSceneNode(id);
	node->attachObject(set);
	node->setPosition(0, 0, 4);
}


void GameEngine::tick()
{
	mPlayer->tick();
	mPlayer->heal(-1);
	updateHUD();
	std::vector<Item *>::iterator itr = mItems.begin();
	while (itr != mItems.end()) {
		if ((*itr)->getInInventory()) {
			itr = mItems.erase(itr);
		} else {
			(*itr)->tick();
			itr++;
		}
		
	}
}


void GameEngine::setKeyState(OIS::KeyCode key, bool pressed) 
{
	mPlayer->feedKey(key, pressed);
}

void GameEngine::updateCamera(Ogre::Camera *camera)
{
	Ogre::Vector3 pos = mPlayer->getPosition();
	camera->setPosition(pos + Ogre::Vector3(0, -80, 80));
	camera->lookAt(pos);
	camera->setNearClipDistance(1);
	camera->setFarClipDistance(500);
}

bool GameEngine::checkCollision(int x, int y)
{
	if (mMap == NULL) {
		return false;
	}
	return mMap->checkCollision(x, y);
}