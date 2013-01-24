add_executable(ActionCrawl
	TutorialApplication.cpp
	BaseApplication.cpp)

target_link_libraries(ActionCrawl ${OGRE_LIBRARIES} ${OIS_LIBRARIES})
