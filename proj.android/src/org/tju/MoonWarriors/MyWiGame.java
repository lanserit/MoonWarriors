package org.tju.MoonWarriors;

import java.util.Random;

import android.util.Log;

import com.wiyun.game.WiGame;


public class MyWiGame{
	
	private static final String APP_KEY ="cdfcf6819044490e";
	private static final String SECRET_KEY ="Nf9kPXszF45yQnEZktkVuKBVNzD9Hjv7";
	private static final String SCORE_LEADERBOARD_ID = "e58fe9b906655628";
	
	public static void startUI()
	{
		Log.i("WIGAME", APP_KEY);
		Log.i("WIGAME", SECRET_KEY);
//		WiGame.initMM(APP_KEY, SECRET_KEY);
//		WiGame.startUI();
		
		WiGame.submitScore(SCORE_LEADERBOARD_ID, new Random().nextInt(3000), null, "test ext value");
	}
	
	public void startWiGameUI()
	{
		final String APP_KEY ="cdfcf6819044490e";
		final String SECRET_KEY ="Nf9kPXszF45yQnEZktkVuKBVNzD9Hjv7";
		Log.i("startWiGameUI", APP_KEY);
		WiGame.initMM(APP_KEY, SECRET_KEY);
		
	}
	
	public static int add(int a, int b){
		return a+b;
	}
}
