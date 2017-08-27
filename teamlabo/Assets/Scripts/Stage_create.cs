using UnityEngine;
using System.Collections;

public class Stage_create: MonoBehaviour {
	public Transform ground;
	public Transform trees1;
	public Transform trees2;
	public int how_long;


	void Start () {
		int p = 0;
		int r = 20;
		for (p = 0; p<how_long ;p++) {
			int q = Random.Range (0,2);
			int i =10;
			r = r + i;
			Vector3 pos_ground = new Vector3(-40+r, -4.0f , 4.0f);
			Vector3 pos_tree = new Vector3(-40+r, -6.7f , 5.0f);
			Quaternion rote = Quaternion.Euler(0, 0, 0);
			if (q == 0) {
				Instantiate (trees1, pos_tree, rote);
			}else if (q == 1) {
				Instantiate (trees2, pos_tree, rote);
			}
			Instantiate (ground, pos_ground, rote);
	}
	}


	void Update () {

	}

		
}
