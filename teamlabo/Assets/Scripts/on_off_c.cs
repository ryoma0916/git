using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class on_off_c : MonoBehaviour {

	void Start () {
		GetComponent<TrailRenderer>().enabled = false;
	}

	void Update () {
		if(Input.GetKey(KeyCode.C)&!Input.GetKey(KeyCode.B)){
			GetComponent<TrailRenderer>().enabled = true;
		}
		else{
			GetComponent<TrailRenderer>().enabled = false;
		}
	}
}
