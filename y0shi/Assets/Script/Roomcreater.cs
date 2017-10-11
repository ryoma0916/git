using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Roomcreater : MonoBehaviour {
		public Transform room1;
		public Transform room2;
		public Transform room3;
	    public Transform room4;
	    int z = 10;

	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		Vector3 pos = new Vector3(this.transform.position.x, this.transform.position.y+z ,this.transform.position.z);
		Quaternion rote = Quaternion.Euler(0, 0, 0);
		if (Input.GetKeyDown (KeyCode.C)) {
			Instantiate (room1, pos, rote);
			z = z + 10;
		}
	}

}
