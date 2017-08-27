using UnityEngine;
using System.Collections;

public class creater: MonoBehaviour {
	bool hit = true;
	public Transform torii1;
	public Transform torii2;
	public Transform torii3;
	public Transform torii4;
	public Transform torii5;
	public Transform torii6;
	public int lv1;
	public int lv2;
	public int lv3;
	void Start () {
		
	}


	void Update () {

	}

	void OnTriggerEnter2D(Collider2D collision) {
		int p;
		int r = 10;
		for (p = 0; p<lv1 ;p++) {
				int q = Random.Range (0,3);
				int i = Random.Range (10,15);
				r = r + i;
				Vector3 pos = new Vector3(this.transform.position.x+r, -4.0f , 0.0f);
				Quaternion rote = Quaternion.Euler(0, 90, 0);
			if (hit & q == 0) {
				Instantiate (torii1, pos, rote);
			}else if (hit & q == 1) {
				Instantiate (torii2, pos, rote);
			}else if (hit & q == 2) {
				Instantiate (torii3, pos, rote);
			}

	}
		if (hit) {
			r = r + 10;
			Vector3 pos1 = new Vector3 (this.transform.position.x + r, -4.0f, 0.0f);
			Quaternion rote1 = Quaternion.Euler (0, 90, 0);
			Instantiate (torii4, pos1, rote1);
		}

		for (p = 0; p<lv2 ;p++) {
			int q = Random.Range (0,3);
			int i = Random.Range (6,10);
			r = r + i;
			Vector3 pos = new Vector3(this.transform.position.x+r, -4.0f , 0.0f);
			Quaternion rote = Quaternion.Euler(0, 90, 0);
			if (hit & q == 0) {
				Instantiate (torii1, pos, rote);
			}else if (hit & q == 1) {
				Instantiate (torii2, pos, rote);
			}else if (hit & q == 2) {
				Instantiate (torii3, pos, rote);
			}
		}
		if (hit) {
			r = r + 10;
			Vector3 pos2 = new Vector3 (this.transform.position.x + r, -4.0f, 0.0f);
			Quaternion rote2 = Quaternion.Euler (0, 90, 0);
			Instantiate (torii5, pos2, rote2);
			for(int i=0;i<100;i++){
				Vector3 pos21 = new Vector3 (this.transform.position.x + r + 10*i, -4.0f, 0.0f);
			}
		}
		for (p = 0; p<lv3 ;p++) {
			int q = Random.Range (0,3);
			int i = Random.Range (6,7);
			r = r + i;
			Vector3 pos = new Vector3(this.transform.position.x+r, -4.0f , 0.0f);
			Quaternion rote = Quaternion.Euler(0, 90, 0);
			if (hit & q == 0) {
				Instantiate (torii1, pos, rote);
			}else if (hit & q == 1) {
				Instantiate (torii2, pos, rote);
			}else if (hit & q == 2) {
				Instantiate (torii3, pos, rote);
			}
		}
		if (hit) {
			r = r + 10;
			Vector3 pos3 = new Vector3 (this.transform.position.x + r, -4.0f, 0.0f);
			Quaternion rote3 = Quaternion.Euler (0, 90, 0);
			Instantiate (torii6, pos3, rote3);
		}
		hit = false;
	}
}
