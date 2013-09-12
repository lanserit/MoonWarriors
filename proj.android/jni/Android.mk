LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := game_shared

LOCAL_MODULE_FILENAME := libgame

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/UnitSprite.cpp \
				   ../../Classes/StartMenu.cpp \
				   ../../Classes/Ship.cpp \
				   ../../Classes/pauseLayer.cpp \
				   ../../Classes/Options.cpp \
				   ../../Classes/LevelManager.cpp \
				   ../../Classes/GameOver.cpp \
				   ../../Classes/GameLayer.cpp \
				   ../../Classes/Enemy.cpp \
				   ../../Classes/Effect.cpp \
				   ../../Classes/Config.cpp \
				   ../../Classes/Bullet.cpp \
				   ../../Classes/About.cpp \
				   ../../Classes/CommonWiGame.cpp
                   
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static cocosdenshion_static cocos_extension_static
            
include $(BUILD_SHARED_LIBRARY)

$(call import-module,CocosDenshion/android) \
$(call import-module,cocos2dx) \
$(call import-module,extensions)

