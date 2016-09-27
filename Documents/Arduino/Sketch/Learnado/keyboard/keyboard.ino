/*
 * 示例程序:
         前置技能：keypad MultiKey示例程序
 */
 
#include <Keyboard.h>
#include <Mouse.h>
#include <Esplora.h>

void setup() 
{
    Serial.begin(9600);       // initialize serial communication with your computer
    delay(8000);
    Mouse.begin();            // take control of the mouse
    Keyboard.begin();
}


void loop() 
{
    int xValue = Esplora.readJoystickX();        // read the joystick's X position
    int yValue = Esplora.readJoystickY();        // read the joystick's Y position
    int button = Esplora.readJoystickSwitch();   // read the joystick pushbutton
    
    Serial.print("Joystick X: ");                // print a label for the X value
    Serial.print(xValue);                        // print the X value
    Serial.print("\tY: ");                       // print a tab character and a label for the Y value
    Serial.print(yValue);                        // print the Y value
    Serial.print("\tButton: ");                  // print a tab character and a label for the button
    Serial.print(button);                        // print the button value
    Serial.println();
  
    int mouseX = map(xValue, -512, 512, 10, -10);  // map the X value to a range of movement for the mouse X
    int mouseY = map(yValue, -512, 512, -10, 10);  // map the Y value to a range of movement for the mouse Y
    Mouse.move(mouseX, mouseY, 0);                 // move the mouse
  
    Keyboard.press(KEY_LEFT_GUI); //send the keychar to keyboard
    Keyboard.release(KEY_LEFT_GUI); //send the keychar to keyboard

    delay(15000);
}  // End loop

/*
 
见文知义keyboard库，功能就是将arduino 模拟成一个usb键盘。
Api如下
Keyboard.begin()
Keyboard.end()
Keyboard.press()
Keyboard.print()
Keyboard.println()
Keyboard.release()
Keyboard.releaseAll()
Keyboard.write() 

Keyboard. press (键值);
输入：键值
    如Keyboard. press(‘A’);
    如Keyboard. press(KEY_LEFT_GUI);//左win
实际输出：
    模拟usb键盘上键值所对应按键被按下

输入键值与按键的对应关系见键值表

Keyboard.release(键值)
输入：键值
    如Keyboard.release(‘A’);
    如Keyboard.release(KEY_LEFT_GUI);//左win
实际输出：
  模拟usb键盘上键值所对应按键被松开

输入键值与按键的对应关系见键值表

PS：Keyboard. press()和Keyboard.release()请成对使用，防止出现按键被按下没有松开的情况

Keyboard.print(character);//模拟键盘敲出一个字符
Keyboard.print(characters);//模拟键盘敲出一串字符的过程
输入：字符或字符串
    如Keyboard.print(“A”);
        Keyboard.print(“ABCDE”);
实际输出
      模拟在usb键盘上敲出单个字符或字符串的过程

Keyboard.println(character)// 模拟键盘敲出一个字符并添加换行的过程
Keyboard.println(characters)// 模拟键盘敲出一串字符并添加换行的过程
输入：字符或字符串
      如Keyboard.print(“A”);
          Keyboard.print(“ABCDE”);
实际输出
       模拟在usb键盘上敲出单个字符或字符串并添加换行的过程

Keyboard.releaseAll()
输入：无

实际输出：释放所有按键；

键值表：
      【from keyboard.h/keyboard.cpp】


一，宏定义部分
   【输入宏定义】
#define     KEY_LEFT_CTRL      0x80
#define     KEY_LEFT_SHIFT     0x81
#define     KEY_LEFT_ALT       0x82
#define     KEY_LEFT_GUI       0x83
#define     KEY_RIGHT_CTRL     0x84
#define     KEY_RIGHT_SHIFT    0x85
#define     KEY_RIGHT_ALT      0x86
#define     KEY_RIGHT_GUI      0x87
#define     KEY_UP_ARROW       0xDA
#define     KEY_DOWN_ARROW     0xD9
#define     KEY_LEFT_ARROW     0xD8
#define     KEY_RIGHT_ARROW    0xD7
#define     KEY_BACKSPACE      0xB2
#define     KEY_TAB            0xB3
#define     KEY_RETURN         0xB0
#define     KEY_ESC            0xB1
#define     KEY_INSERT         0xD1
#define     KEY_DELETE         0xD4
#define     KEY_PAGE_UP        0xD3
#define     KEY_PAGE_DOWN      0xD6
#define     KEY_HOME           0xD2
#define     KEY_END            0xD5
#define     KEY_CAPS_LOCK      0xC1
#define     KEY_F1             0xC2
#define     KEY_F2             0xC3
#define     KEY_F3             0xC4
#define     KEY_F4             0xC5
#define     KEY_F5             0xC6
#define     KEY_F6             0xC7
#define     KEY_F7             0xC8
#define     KEY_F8             0xC9
#define     KEY_F9             0xCA
#define     KEY_F10            0xCB
#define     KEY_F11            0xCC
#define     KEY_F12            0xCD

二，ascii 码部分
   【输入注释里的字符的ascii码】
0x2a,             // BS    Backspace
0x2b,             // TAB    Tab
0x28,             // LF    Enter
0x2c,             //  ' '
0x1e|SHIFT,       // !
0x34|SHIFT,       // "
0x20|SHIFT,       // #
0x21|SHIFT,       // $
0x22|SHIFT,       // %
0x24|SHIFT,       // &
0x34,             // '
0x26|SHIFT,       // (
0x27|SHIFT,       // )
0x25|SHIFT,       // *
0x2e|SHIFT,       // +
0x36,             // ,
0x2d,             // -
0x37,             // .
0x38,             // /
0x27,             // 0
0x1e,             // 1
0x1f,             // 2
0x20              // 3
0x21,             // 4
0x22,             // 5
0x23,             // 6
0x24,             // 7
0x25,             // 8
0x26,             // 9
0x33|SHIFT,       // :
0x33,             // ;
0x36|SHIFT,       // <
0x2e,             // =
0x37|SHIFT,       // >
0x38|SHIFT,       // ?
0x1f|SHIFT,       // @
0x04|SHIFT,       // A
0x05|SHIFT,       // B
0x06|SHIFT,       // C
0x07|SHIFT,       // D
0x08|SHIFT,       // E
0x09|SHIFT,       // F
0x0a|SHIFT,       // G
0x0b|SHIFT,       // H
0x0c|SHIFT,       // I
0x0d|SHIFT,       // J
0x0e|SHIFT,       // K
0x0f|SHIFT,       // L
0x10|SHIFT,       // M
0x11|SHIFT,       // N
0x12|SHIFT,       // O
0x13|SHIFT,       // P
0x14|SHIFT,       // Q
0x15|SHIFT,       // R
0x16|SHIFT,       // S
0x17|SHIFT,       // T
0x18|SHIFT,       // U
0x19|SHIFT,       // V
0x1a|SHIFT,       // W
0x1b|SHIFT,       // X
0x1c|SHIFT,       // Y
0x1d|SHIFT,       // Z
0x2f,             // [
0x31,             // bslash
0x30,             // ]
0x23|SHIFT,       // ^
0x2d|SHIFT,       // _
0x35,             // `
0x04,             // a
0x05,             // b
0x06,             // c
0x07,             // d
0x08,             // e
0x09,             // f
0x0a,             // g
0x0b,             // h
0x0c,             // i
0x0d,             // j
0x0e,             // k
0x0f,             // l
0x10,             // m
0x11,             // n
0x12,             // o
0x13,             // p
0x14,             // q
0x15,             // r
0x16,             // s
0x17,             // t
0x18,             // u
0x19,             // v
0x1a,             // w
0x1b,             // x
0x1c,             // y
0x1d,             // z
0x2f|SHIFT,       // {
0x31|SHIFT,       // |
0x30|SHIFT,       // }
0x35|SHIFT,       // ~

 */
