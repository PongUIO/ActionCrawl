add_executable(ActionCrawl npc_types/puppy.cpp npc.cpp ../gorilla/Gorilla.cpp inventory.cpp item.cpp tilesetmanager.cpp maptile.cpp gamemap.cpp gameengine.cpp player.cpp creature.cpp
	baseapplication.cpp healthbar.cpp)

target_link_libraries(ActionCrawl ${OGRE_LIBRARIES} ${OIS_LIBRARIES})

add_subdirectory(npc_types)