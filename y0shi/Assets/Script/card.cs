using UnityEngine;
using System.Collections;
using UnityEngine.UI;


public class card : MonoBehaviour {

	public GameObject Card;
	public string card_name;
	public Text cardtext; //Text用変数
	public string power; //スコア計算用変数
	//********** 終了 **********//

	void Start (){
		//********** 開始 **********//
		 //初期スコアを代入して画面に表示
		//********** 終了 **********//
	}

	void Update (){
		if (Input.GetKeyDown (KeyCode.A)) {
			cardtext.text = name + ":" + power.ToString ();
			}
		if (Input.GetKey(KeyCode.A)&&Input.GetKeyDown (KeyCode.B)) {
			Card.SetActive (false);
		}
	}
}
