#include "Keyboard.h"

#define Button1 15
#define Button2 14
#define Button3 10
#define Button4 9

void setup() {
  Keyboard.begin();
  pinMode(Button1, INPUT_PULLUP);
  pinMode(Button2, INPUT_PULLUP);
  pinMode(Button3, INPUT_PULLUP);
  pinMode(Button4, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(Button3) == LOW) { // コピー

    Keyboard.print("`````(%```(}`(<_```._``.:_```_``````````._` ` (< ``(:_``` :_``` __J!``_`j<``.```"); Keyboard.write('\n');
    Keyboard.print("`` ` ``````` ;<``` ( ` (<~` `_``-```````(``_``.+<`_(<+.``.:;-```<_~`` (.`_`` _``"); Keyboard.write('\n');
    Keyboard.print("`.``.```````.<<`` .z_ `::_```_``_ ````` ~` _``.<<`` _;< __(<<.``(_````._` _``( `"); Keyboard.write('\n');
    Keyboard.print(" _` _`````.`_(<`._(<_``<:_```_``_ `````._` ```.;<_` _:~_``_(<>- .<.```.<``_`` <`"); Keyboard.write('\n');
    Keyboard.print("(~`.  ````` ~.:`` <~_``<:_  `_` _       _ _```.:<_` _(__.`_(:~_..<-``` (-`. ``(_"); Keyboard.write('\n');
    Keyboard.print("<` __``````   <``.<` `.~:_``` ` < `````.`-````_:;_` _ _     :<-..>``   _<.`~`` <"); Keyboard.write('\n');
    Keyboard.print("<.-._```.`._``_`.(~``_ _;~`` ___<-```` _-.-``._(<-.-.._.-_ `_~ _.>.`. ``(:`(.`.("); Keyboard.write('\n');
    Keyboard.print("_.__ `````._` .. <~` _.((gJJ-./ <<````_-``_``. :~_.a&gmgj.._<_`_(>`..``. +-._``."); Keyboard.write('\n');
    Keyboard.print(".-.-.`.``.`.``( .(_ .gR(WBYYHMN1I<_``.~``.<``_ :(%.MB9YWWM#Nm-..<:``..```(:-_.`."); Keyboard.write('\n');
    Keyboard.print(" __...`.``  . :_..<jMM6<<7MMNm<>j<... ````~`. .<T1>~_7MNm+?WNN, _<. _._.`.>~-_.."); Keyboard.write('\n');
    Keyboard.print(". ._``.._.. `.;_. dM#<--`.WMMMh._~_ .```` ~ _ _`.!.-`.dMMMc<dMN,._`._ _.`.<-__``"); Keyboard.write('\n');
    Keyboard.print("__.~``.._._.`(: .(WM3~JNKC~.TMM[._~` .``` `.`. .`.#MR>`?WMN.<MM5_.._`-_.`.(<--_."); Keyboard.write('\n');
    Keyboard.print("_~ ~...~.`(..(< ` .H< HH$.  .(T%` ._` _`._.`     ,MW-. ..WH_(MF._`._.-<`..(1___."); Keyboard.write('\n');
    Keyboard.print("-_._ .(...(-.(1.``` !`/KI<~_(<.        ~..       .RZv<_<<`! (Y _ ._``(<.`.-l>-__"); Keyboard.write('\n');
    Keyboard.print("_._...>``.(z-(z<```````(S,`  J'         _         (I`   (~` ! _`->...+~`..-Oz-(<"); Keyboard.write('\n');
    Keyboard.print("_._.-+~...-zo_1+_```..-..___.                       <<<<_.. .~.(<:...v_....lOo.<"); Keyboard.write('\n');
    Keyboard.print("~-_.(v_..`.jr1-<1 ....____~.                         ..~.__(~-_J<:..(v..`..jvO-<"); Keyboard.write('\n');
    Keyboard.print("._.-z>.....(wG+-<:`........                          ....-_~_-+><:.-Z>.....(vzI<"); Keyboard.write('\n');
    Keyboard.print(".~.(X>..`.. jxuo1<.                    (<                _`.(+z&v:-JZ~....._vuXz"); Keyboard.write('\n');
    Keyboard.print("_._zX>......-OuuZGo~.                 +??1.              ._~ Juu2_JXC....`..Ou0d"); Keyboard.write('\n');
    Keyboard.print("_.(uX{....`..zuyyyWI-`               .??=z:                 .wZVidZ0~.......(ZjX"); Keyboard.write('\n');
    Keyboard.print("_~JZZI.......(ZyyWVXn.                !<<!                .JXyXdyyXC........_(XZ"); Keyboard.write('\n');
    Keyboard.print("<_wyWX-......(ZyVWVWWkG.                                .uXWWHVVVWD_........-dyZ"); Keyboard.write('\n');

       
    while (digitalRead(Button1) == LOW);
  }

  delay(100);
}
