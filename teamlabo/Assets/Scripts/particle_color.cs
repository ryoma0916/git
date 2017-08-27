using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class particle_color : MonoBehaviour {

	void Start () {
		gameObject.GetComponent<ParticleSystem>().startColor = Color.clear;
	}

	void Update () {
		if(Input.GetKey(KeyCode.C)&Input.GetKey(KeyCode.B)){
			gameObject.GetComponent<ParticleSystem>().startColor = Color.green;
		}
		else if(Input.GetKey(KeyCode.C)&!Input.GetKey(KeyCode.B)){
			gameObject.GetComponent<ParticleSystem>().startColor = Color.blue;
		}else if(!Input.GetKey(KeyCode.C)&Input.GetKey(KeyCode.B)){
			gameObject.GetComponent<ParticleSystem>().startColor = Color.red;
		}else{
			gameObject.GetComponent<ParticleSystem>().startColor = Color.clear;
		}
	}
}
