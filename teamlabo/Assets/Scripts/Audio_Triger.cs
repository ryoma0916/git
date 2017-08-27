using UnityEngine;
using System.Collections;

public class Audio_Triger: MonoBehaviour {
	private AudioSource[] sources;
	bool hit = true;
	void Start () {
		sources = gameObject.GetComponents<AudioSource>();
	}


	void Update () {

	}

	void OnTriggerEnter2D(Collider2D collision) {
		if (hit) {
			int i = Random.Range (0, 3);
			string Tag = collision.gameObject.tag;
			sources [i].Play ();
			hit = false;
		}
	}
}
