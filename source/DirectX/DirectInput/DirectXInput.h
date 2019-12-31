#pragma once

#define DIRECTINPUT_VERSION     0x0800          // DirectInputのバージョン指定
#include <dinput.h>
#include <Windows.h>

#pragma comment(lib , "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

// DIKをMSKに変更 MslibKeyType
#define MSK_ESCAPE          DIK_ESCAPE         
#define MSK_1               DIK_1              
#define MSK_2               DIK_2              
#define MSK_3               DIK_3              
#define MSK_4               DIK_4              
#define MSK_5               DIK_5              
#define MSK_6               DIK_6              
#define MSK_7               DIK_7              
#define MSK_8               DIK_8              
#define MSK_9               DIK_9              
#define MSK_0               DIK_0              
#define MSK_MINUS           DIK_MINUS          
#define MSK_EQUALS          DIK_EQUALS         
#define MSK_BACK            DIK_BACK           
#define MSK_TAB             DIK_TAB            
#define MSK_Q               DIK_Q              
#define MSK_W               DIK_W              
#define MSK_E               DIK_E              
#define MSK_R               DIK_R              
#define MSK_T               DIK_T              
#define MSK_Y               DIK_Y              
#define MSK_U               DIK_U              
#define MSK_I               DIK_I              
#define MSK_O               DIK_O              
#define MSK_P               DIK_P              
#define MSK_LBRACKET        DIK_LBRACKET       
#define MSK_RBRACKET        DIK_RBRACKET       
#define MSK_RETURN          DIK_RETURN         
#define MSK_LCONTROL        DIK_LCONTROL       
#define MSK_A               DIK_A              
#define MSK_S               DIK_S              
#define MSK_D               DIK_D              
#define MSK_F               DIK_F              
#define MSK_G               DIK_G              
#define MSK_H               DIK_H              
#define MSK_J               DIK_J              
#define MSK_K               DIK_K              
#define MSK_L               DIK_L              
#define MSK_SEMICOLON       DIK_SEMICOLON      
#define MSK_APOSTROPHE      DIK_APOSTROPHE     
#define MSK_GRAVE           DIK_GRAVE          
#define MSK_LSHIFT          DIK_LSHIFT         
#define MSK_BACKSLASH       DIK_BACKSLASH      
#define MSK_Z               DIK_Z              
#define MSK_X               DIK_X              
#define MSK_C               DIK_C              
#define MSK_V               DIK_V              
#define MSK_B               DIK_B              
#define MSK_N               DIK_N              
#define MSK_M               DIK_M              
#define MSK_COMMA           DIK_COMMA          
#define MSK_PERIOD          DIK_PERIOD         
#define MSK_SLASH           DIK_SLASH          
#define MSK_RSHIFT          DIK_RSHIFT         
#define MSK_MULTIPLY        DIK_MULTIPLY       
#define MSK_LMENU           DIK_LMENU          
#define MSK_SPACE           DIK_SPACE          
#define MSK_CAPITAL         DIK_CAPITAL        
#define MSK_F1              DIK_F1             
#define MSK_F2              DIK_F2             
#define MSK_F3              DIK_F3             
#define MSK_F4              DIK_F4             
#define MSK_F5              DIK_F5             
#define MSK_F6              DIK_F6             
#define MSK_F7              DIK_F7             
#define MSK_F8              DIK_F8             
#define MSK_F9              DIK_F9             
#define MSK_F10             DIK_F10            
#define MSK_NUMLOCK         DIK_NUMLOCK        
#define MSK_SCROLL          DIK_SCROLL         
#define MSK_NUMPAD7         DIK_NUMPAD7        
#define MSK_NUMPAD8         DIK_NUMPAD8        
#define MSK_NUMPAD9         DIK_NUMPAD9        
#define MSK_SUBTRACT       	DIK_SUBTRACT       
#define MSK_NUMPAD4        	DIK_NUMPAD4        
#define MSK_NUMPAD5        	DIK_NUMPAD5        
#define MSK_NUMPAD6        	DIK_NUMPAD6        
#define MSK_ADD            	DIK_ADD            
#define MSK_NUMPAD1        	DIK_NUMPAD1        
#define MSK_NUMPAD2        	DIK_NUMPAD2        
#define MSK_NUMPAD3        	DIK_NUMPAD3        
#define MSK_NUMPAD0        	DIK_NUMPAD0        
#define MSK_DECIMAL        	DIK_DECIMAL        
#define MSK_OEM_102        	DIK_OEM_102        
#define MSK_F11            	DIK_F11            
#define MSK_F12            	DIK_F12            
#define MSK_F13            	DIK_F13            
#define MSK_F14            	DIK_F14            
#define MSK_F15            	DIK_F15            
#define MSK_KANA           	DIK_KANA           
#define MSK_ABNT_C1        	DIK_ABNT_C1        
#define MSK_CONVERT        	DIK_CONVERT        
#define MSK_NOCONVERT      	DIK_NOCONVERT      
#define MSK_YEN            	DIK_YEN            
#define MSK_ABNT_C2        	DIK_ABNT_C2        
#define MSK_NUMPADEQUALS   	DIK_NUMPADEQUALS   
#define MSK_PREVTRACK      	DIK_PREVTRACK      
#define MSK_AT             	DIK_AT             
#define MSK_COLON          	DIK_COLON          
#define MSK_UNDERLINE      	DIK_UNDERLINE      
#define MSK_KANJI          	DIK_KANJI          
#define MSK_STOP           	DIK_STOP           
#define MSK_AX             	DIK_AX             
#define MSK_UNLABELED      	DIK_UNLABELED      
#define MSK_NEXTTRACK      	DIK_NEXTTRACK      
#define MSK_NUMPADENTER    	DIK_NUMPADENTER    
#define MSK_RCONTROL       	DIK_RCONTROL       
#define MSK_MUTE           	DIK_MUTE           
#define MSK_CALCULATOR     	DIK_CALCULATOR     
#define MSK_PLAYPAUSE      	DIK_PLAYPAUSE      
#define MSK_MEDIASTOP      	DIK_MEDIASTOP      
#define MSK_VOLUMEDOWN     	DIK_VOLUMEDOWN     
#define MSK_VOLUMEUP       	DIK_VOLUMEUP       
#define MSK_WEBHOME        	DIK_WEBHOME        
#define MSK_NUMPADCOMMA    	DIK_NUMPADCOMMA    
#define MSK_DIVIDE         	DIK_DIVIDE         
#define MSK_SYSRQ          	DIK_SYSRQ          
#define MSK_RMENU          	DIK_RMENU          
#define MSK_PAUSE          	DIK_PAUSE          
#define MSK_HOME           	DIK_HOME           
#define MSK_UP             	DIK_UP             
#define MSK_PRIOR          	DIK_PRIOR          
#define MSK_LEFT           	DIK_LEFT           
#define MSK_RIGHT          	DIK_RIGHT          
#define MSK_END            	DIK_END            
#define MSK_DOWN           	DIK_DOWN           
#define MSK_NEXT           	DIK_NEXT           
#define MSK_INSERT         	DIK_INSERT         
#define MSK_DELETE         	DIK_DELETE         
#define MSK_LWIN           	DIK_LWIN           
#define MSK_RWIN           	DIK_RWIN           
#define MSK_APPS           	DIK_APPS           
#define MSK_POWER          	DIK_POWER          
#define MSK_SLEEP          	DIK_SLEEP          
#define MSK_WAKE           	DIK_WAKE           
#define MSK_WEBSEARCH      	DIK_WEBSEARCH      
#define MSK_WEBFAVORITES   	DIK_WEBFAVORITES   
#define MSK_WEBREFRESH     	DIK_WEBREFRESH     
#define MSK_WEBSTOP        	DIK_WEBSTOP        
#define MSK_WEBFORWARD     	DIK_WEBFORWARD     
#define MSK_WEBBACK        	DIK_WEBBACK        
#define MSK_MYCOMPUTER     	DIK_MYCOMPUTER     
#define MSK_MAIL            DIK_MAIL           
#define MSK_MEDIASELECT     DIK_MEDIASELECT    

#define MSK_BACK             DIK_BACK           
#define MSK_MULTIPLY         DIK_MULTIPLY       
#define MSK_LMENU            DIK_LMENU          
#define MSK_CAPITAL          DIK_CAPITAL        
#define MSK_SUBTRACT         DIK_SUBTRACT       
#define MSK_ADD              DIK_ADD            
#define MSK_DECIMAL          DIK_DECIMAL        
#define MSK_DIVIDE           DIK_DIVIDE         
#define MSK_RMENU            DIK_RMENU          
#define MSK_UP               DIK_UP             
#define MSK_PRIOR            DIK_PRIOR          
#define MSK_LEFT             DIK_LEFT           
#define MSK_RIGHT            DIK_RIGHT          
#define MSK_DOWN             DIK_DOWN           
#define MSK_NEXT             DIK_NEXT           

#define MSK_CIRCUMFLEX      DIK_PREVTRACK     

#define MSK_MAX				256

namespace mslib {
namespace directx {
class DirectXInput {
public:
	DirectXInput();
	~DirectXInput();

	void Init(HINSTANCE _hIncetance);

	// キー入力が入った時
	bool GetKeyEnter(unsigned int _key);
	// キー入力が終わった時
	bool GetKeyExit(unsigned int _key);
	// キー入力中
	bool GetKeyStay(unsigned int _key);

	// 何かキーが押された時
	bool GetAnyEnter();
	// 何かキーが押されている時
	bool GetAnyStay();

	void Update();
private:
	LPDIRECTINPUT8    m_dxInput= nullptr;        // DirectInputオブジェクト
	LPDIRECTINPUTDEVICE8    m_dxKeyInoutDevice = nullptr;             // キーボードデバイス

	// staticで宣言したいのでInitを一度しかできないようにする
	bool m_once = true;
																	  // キーの入力
	BYTE m_key[MSK_MAX];
	BYTE m_oldKey[MSK_MAX];
};
}
}