using UnityEngine;
using System.Collections;
using UnityEngine.SceneManagement;

public class Life: MonoBehaviour {

	public int life ;
	public GameObject Score;
	bool hit = true;
	void Start () {

	}


	void Update () {

	}

	void OnTriggerEnter2D(Collider2D collision) {
		string Tag  = collision.gameObject.tag;
		if (Tag == "pa" && !Input.GetKey (KeyCode.C) && !Input.GetKey (KeyCode.B)) {
			damage ();
		} else if (Tag == "pa" && !Input.GetKey (KeyCode.C) && Input.GetKey (KeyCode.B)) {
			damage ();
		} else if (Tag == "pa" && Input.GetKey (KeyCode.C) && !Input.GetKey (KeyCode.B)) {
			damage ();
		} else if (Tag == "right" & !Input.GetKey (KeyCode.B)) {
			damage ();
		} else if (Tag == "left" & !Input.GetKey (KeyCode.C)) {
			damage ();
		}else if (Tag == "left" & Input.GetKey (KeyCode.B)) {
			damage ();
		} else if (Tag == "right" & Input.GetKey (KeyCode.C)) {
			damage ();
		}else if (Tag == "damage") {
			damage ();
		}
		else if (Tag == "goal") {
			int sceneIndex = SceneManager.GetActiveScene().buildIndex;
			SceneManager.LoadScene("goal");
		}
		if (life == -2 ) {
			int sceneIndex = SceneManager.GetActiveScene().buildIndex;
			SceneManager.LoadScene("title");
		}
	}
	void damage(){
		life = life - 1;
		hit = false;
		Score.SendMessage ("Damage", -1);
	}
}