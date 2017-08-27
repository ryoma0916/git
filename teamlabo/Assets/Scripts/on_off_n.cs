using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class on_off_n : MonoBehaviour {

	// Use this for initialization
	void Start () {
		GetComponent<TrailRenderer>().enabled = true;
	}

	void Update () {
		if(Input.GetKey(KeyCode.C)){
			GetComponent<TrailRenderer>().enabled = false;
		}
		else if(Input.GetKey(KeyCode.B)){
			GetComponent<TrailRenderer>().enabled = false;
		}
		else{
			GetComponent<TrailRenderer>().enabled = true;
		}
	}
}
