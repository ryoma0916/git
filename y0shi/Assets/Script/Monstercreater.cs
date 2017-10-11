using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Monstercreater : MonoBehaviour {

	public Transform monster1;
	public Transform monster2;
	public Transform monster3;
	void Start () {
		
	}

	void Update () {
			GameObject obj = getClickObject ();
		if (obj != null) {
		/*	Vector3 pos = new Vector3(obj.transform.position.x, obj.transform.position.y, obj.transform.position.z+2);
			Quaternion rote = Quaternion.Euler(0, 0, 0);
			Instantiate (monster1, pos, rote);
		*/
			Destroy (obj);
				}
		}
	private GameObject getClickObject() {
		GameObject result = null;
		if(Input.GetMouseButtonDown(0)) {
			Vector3 tapPoint = Camera.main.ScreenToWorldPoint(Input.mousePosition);
			Collider2D collition2d = Physics2D.OverlapPoint(tapPoint);
			if (collition2d) {
				result = collition2d.transform.gameObject;
				}
			}
		return result;
	}

}
