using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class on_off : MonoBehaviour {

	void Start () {
		GetComponent<MaterialChangeTester>().enabled = false;
	}

	void Update () {

	}
	void OnCollisionEnter2D(Collision2D collision) {
		GetComponent<MaterialChangeTester>().enabled = true;
	}
}

