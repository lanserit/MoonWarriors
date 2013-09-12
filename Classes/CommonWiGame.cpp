/*	
#include "CommonWiGame.h"
#include <jni.h>
#include "platform/android/jni/JniHelper.h"

//#if ( CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID )
#include "cocos2d.h"
//#endif

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
	void startWiGameUI(){
		 
		JavaVM* jvm = cocos2d::JniHelper::getJavaVM();
		JNIEnv *env = NULL;
		// get jni environment
		if( jvm->GetEnv((void**)&env, JNI_VERSION_1_4)!=JNI_OK )
		{
			int status = jvm->AttachCurrentThread(&env,NULL);
			if(status<0){
				return;
			}
		}else{
			return;
		} 
		jclass clazz = env->FindClass("org/tju/MoonWarriors/MyWiGame");
		jmethodID mid = env->GetStaticMethodID(clazz,"startUI","()V");
		env->CallStaticVoidMethod(clazz,mid);
		
		env->DeleteLocalRef(clazz); 
	}
//#endif


#ifdef __cplusplus
}
#endif // __cplusplus
*/

#include "CommonWiGame.h" 
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include <android/log.h>
   
void startWiGameUI(){
	JniMethodInfo method; 
    bool b = JniHelper::getStaticMethodInfo(method, "org.tju.MoonWarriors.MoonWarriors", "startUI", "()V");
    if(b) { 
        method.env->CallStaticVoidMethod(method.classID, method.methodID); 
    }
}

void startScoreRankUI(int score){
	JniMethodInfo method; 
    bool b = JniHelper::getStaticMethodInfo(method, "org.tju.MoonWarriors.MoonWarriors", "startScoreRankUI", "(I)V");
    if(b) { 
        method.env->CallStaticVoidMethod(method.classID, method.methodID, score); 
    }
}

