add_executable(ActionCrawl inventory.cpp item.cpp tilesetmanager.cpp maptile.cpp gamemap.cpp gameengine.cpp player.cpp creature.cpp
	baseapplication.cpp)

target_link_libraries(ActionCrawl ${OGRE_LIBRARIES} ${OIS_LIBRARIES})
