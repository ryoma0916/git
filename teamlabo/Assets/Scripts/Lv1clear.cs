using UnityEngine;
using System.Collections;
using UnityEngine.SceneManagement;

public class Lv1clear : MonoBehaviour {

	public GameObject lv1;

	void Start () {
		lv1.SetActive(false);

	}

	void Update () {
		
	}

	void OnTriggerEnter2D(Collider2D collision) {
		string Tag  = collision.gameObject.tag;
		if (Tag == "player") {
			lv1.SetActive(true);
		}
}
}
