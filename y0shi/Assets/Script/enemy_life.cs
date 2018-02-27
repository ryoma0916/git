
using UnityEngine;
using System.Collections;
using UnityEngine.UI;


public class enemy_life : MonoBehaviour {

	public GameObject enemy;
	public Text lifeText; //Text用変数
	private int life = 100; //スコア計算用変数
	//********** 終了 **********//

	void Start (){
		//********** 開始 **********//
		lifeText.text = "Life:"+ life.ToString(); //初期スコアを代入して画面に表示
		//********** 終了 **********//
	}

	void Update (){
		if (Input.GetKeyDown(KeyCode.S)) {
			life = life-10;
			lifeText.text = "Life: " + life.ToString();
		}
		if (life == 0) {
			enemy.SetActive (false);
		}
	}
}
