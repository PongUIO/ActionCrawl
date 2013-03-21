#include "gameengine.h"
#include "player.h"

GameEngine::GameEngine(Ogre::SceneManager *manager, Gorilla::Screen *screen)
{
	mScreen = screen;
	mInitialized = false;
	mSceneMgr = manager;
	mMap = NULL;
	mHUDSizeFactor = 1.1;
	mOverlayMgr = Ogre::OverlayManager::getSingletonPtr();
	mInventoryOverlay = mOverlayMgr->create("GameEngine_inventory");
	mActiveList = NONELIST;
}

void GameEngine::setHUDSizeFactor(double factor) {
	mHUDSizeFactor = std::max(0.1, factor);
	resizeHUD();
}

GameEngine::~GameEngine()
{
	delete mPlayer;
	
}

void GameEngine::init()
{
	
	Ogre::ResourceManager::ResourceMapIterator font = Ogre::FontManager::getSingleton().getResourceIterator();
	
	while( font.hasMoreElements() )
	{
		font.getNext()->load();
	}
	
	mPlayer = new Player(this);
	mPlayer->getPosition() = Ogre::Vector3(5*WORLDSCALE,5*WORLDSCALE,0);
	addBillboardItemToWorld(*mPlayer, "playerNode");
	
	Item *item = new Item(this);
	item->getPosition() = Ogre::Vector3(5*WORLDSCALE,5*WORLDSCALE,0);
	mItems.push_back(item);
	addBillboardItemToWorld(*item, "itemNode");
	
	item = new Item(this);
	item->getPosition() = Ogre::Vector3(10*WORLDSCALE,5*WORLDSCALE,0);
	mItems.push_back(item);
	addBillboardItemToWorld(*item, "itemNode2");
	
	mMap = new GameMap(256, 256, DUNGEON, mSceneMgr, &mTileSetMgr);
	mInitialized = true;
	mLayer = mScreen->createLayer(0);
	mBackgroundRect = mLayer->createRectangle(0, 0, 0, 0);
	mHealthBarRect = mLayer->createRectangle(0, 0, 0, 0);
	resizeHUD();
}

void GameEngine::resizeHUD()
{
	mBackgroundRect->position(0, mScreen->getHeight()-150*mHUDSizeFactor);
	mBackgroundRect->width(200*mHUDSizeFactor);
	mBackgroundRect->height(150*mHUDSizeFactor);
	mHealthBarRect->position(20*mHUDSizeFactor, mScreen->getHeight() - 130*mHUDSizeFactor);
	mHealthBarRect->height(20*mHUDSizeFactor);
	updateHUD();
}

void GameEngine::updateHUD() 
{
	float prop = double(mPlayer->getHealth())/mPlayer->getMaxHealth();
	mHealthBarRect->background_colour(Gorilla::rgb(240, 40-prop/4, 40-prop/4));
	mHealthBarRect->width(prop*160*mHUDSizeFactor);
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
	if (mActiveList != NONELIST) {
		return;
	}
	mPlayer->tick();
	mPlayer->heal(1);
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
	while (itr != mCreatures.end()) {
		if ((*itr)->getInInventory()) {
			itr = mCreatures.erase(itr);
		} else {
			(*itr)->tick();
			itr++;
		}
		
	}
}


void GameEngine::setKeyState(OIS::KeyCode key, bool pressed) 
{
	if (!mActiveList != NONELIST) {
		mPlayer->feedKey(key, pressed);
	}
	if (key == OIS::KC_I && pressed) {
		if (mActiveList == NONELIST) {
			mActiveList = INVENTORY;
			createBillboardScreen(INVENTORY);
		} else if (mActiveList == INVENTORY) {
			mActiveList = NONELIST;
			removeBillboardScreen();
		}
	}
}

void GameEngine::createBillboardScreen(BillboardListType type)
{
	Ogre::String scrType = "Inventory";
	Ogre::String materialType = "inventory";
	Ogre::OverlayContainer *bg = static_cast<Ogre::OverlayContainer *>(
		mOverlayMgr->createOverlayElement("Panel", "itembg"));
	bg->setMetricsMode(Ogre::GMM_RELATIVE);
	bg->setDimensions(1-ICONRELDIST*2, 1-ICONRELDIST*2);
	bg->setPosition(ICONRELDIST, ICONRELDIST);
	bg->setMaterialName(materialType);
	Ogre::TextAreaOverlayElement *listType = static_cast<Ogre::TextAreaOverlayElement*>
		(mOverlayMgr->createOverlayElement("TextArea", scrType));
	listType->setMetricsMode(Ogre::GMM_RELATIVE);
	listType->setPosition(ICONRELSIZE - ICONRELDIST, ICONRELSIZE);
	listType->setDimensions(1,1);
	listType->setCharHeight(ICONRELSIZE);
	listType->setColour(Ogre::ColourValue(0.6, 0.6, 0.6));
	listType->setCaption(scrType);
	listType->setFontName("bluecond");
	bg->addChild(listType);
	mInventoryOverlay->add2D(bg);
	Inventory &inv = mPlayer->getInventory();
	for (int i = 0; i < inv.getNumberOfItems(); i++) {
		Item *item = inv.getItem(i);
		Ogre::String tmp = "img" + item->getSceneName();
		Ogre::OverlayContainer *element = static_cast<Ogre::OverlayContainer *>
		(mOverlayMgr->createOverlayElement("Panel", tmp));
		element->setMetricsMode(Ogre::GMM_RELATIVE);
		element->setMaterialName(item->getResID());
		element->setPosition(ICONRELSIZE,(ICONRELSIZE + ICONRELDIST)*(i+2));
		element->setDimensions(ICONRELSIZE, ICONRELSIZE);
		Ogre::TextAreaOverlayElement *textarea = static_cast<Ogre::TextAreaOverlayElement*>
		(mOverlayMgr->createOverlayElement("TextArea", item->getSceneName()));
		textarea->setMetricsMode(Ogre::GMM_RELATIVE);
		textarea->setFontName("bluecond");
		textarea->setCharHeight(ICONRELSIZE);
		textarea->setDimensions(1,1);
		textarea->setColour(Ogre::ColourValue(0.6, 0.6, 0.6));
		textarea->setCaption(item->getName());
		textarea->setPosition(ICONRELSIZE + ICONRELDIST, 0.0);
		element->addChild(textarea);
		mInventoryOverlay->add2D(element);
	}
	mInventoryOverlay->show();

}

void GameEngine::removeBillboardScreen()
{
	Ogre::Overlay::Overlay2DElementsIterator itr = mInventoryOverlay->get2DElementsIterator();
	while (itr.hasMoreElements()) {
		Ogre::OverlayContainer *tmp = itr.getNext();
		auto children = tmp->getChildIterator();
		while (children.hasMoreElements()) {
			auto chld = children.getNext();
			mOverlayMgr->destroyOverlayElement(chld->getName());
		}
		mInventoryOverlay->remove2D(tmp);
		mOverlayMgr->destroyOverlayElement(tmp);
	}
	mInventoryOverlay->clear();
	mInventoryOverlay->hide();

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