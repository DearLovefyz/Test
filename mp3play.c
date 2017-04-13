#include "mp3play.h"

static int DoublekeyTime = 0;		//double keydown time
static BOOL DoubleKeyDown = FALSE;	//double keydown flag
static BOOL StartTiming = FALSE;	//keyup start timing flag
#define DOUBLE_KEY_TIMER_ID 35	//double keydown TimerID

static void MP3_APlayP_OnKeyDown( KEY Key, QUAD lParam )
{
	switch(Key)
	{

	case TIDE_EAR_MIC_K:
		DownKey = TIDE_EAR_MIC_K;
		if(StartTiming == TRUE){//第一次按下弹起0.5s内为真，在此期间按下即触发
			DoubleKeyDown = TRUE;
			StartTiming = FALSE;
			DoublekeyTime = 0;
			Timer_KillTimer(DOUBLE_KEY_TIMER_ID);
			
		}	
	break;

	}
}

static void MP3_OnKeyUp(void)
{
	switch(DownKey)
	{
		
	case TIDE_EAR_MIC_K:	
		DownKey = 0;
		if(DoubleKeyDown == FALSE){
			StartTiming = TRUE;
			Timer_SetTimer(DOUBLE_KEY_TIMER_ID, 100, TRUE);
		}
		else{	
			Handler_PostMessage(-1, MSG_KEYDOWN, TIDE_RIGHT_K, 0);
			Handler_PostMessage(-1, MSG_KEYUP, TIDE_RIGHT_K, 0);//连按两下的第二次弹起操作，切歌
			DoubleKeyDown = FALSE;
		}
	break;

	}
}

static void MP3_APlayP_OnTimer(WORD wTimerID)
{
		
	if(wTimerID == DOUBLE_KEY_TIMER_ID)
	{
		DoublekeyTime++;
		if(DoublekeyTime > 5) {//当第一次按下弹起之后0.5s内没有再按下，则触发暂停或播放
			DoublekeyTime = 0;
			DoubleKeyDown = FALSE;
			StartTiming = FALSE;
			Timer_KillTimer(DOUBLE_KEY_TIMER_ID);
			Handler_PostMessage(-1, MSG_KEYDOWN, TIDE_SOFT3_K, 0);
			Handler_PostMessage(-1, MSG_KEYUP, TIDE_SOFT3_K, 0);
		}
	}

}	
