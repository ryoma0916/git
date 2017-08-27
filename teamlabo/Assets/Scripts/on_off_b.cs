using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class on_off_b : MonoBehaviour {

	void Start () {
		GetComponent<TrailRenderer>().enabled = false;
	}

	void Update () {
		if(Input.GetKey(KeyCode.B)&!Input.GetKey(KeyCode.C)){
		GetComponent<TrailRenderer>().enabled = true;
		}
		else{
			GetComponent<TrailRenderer>().enabled = false;
		}
	}
}
