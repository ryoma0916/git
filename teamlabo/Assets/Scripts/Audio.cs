using UnityEngine;
using System.Collections;

public class Audio: MonoBehaviour {
	private AudioSource[] sources;
	void Start () {
		sources = gameObject.GetComponents<AudioSource>();
	}


	void Update () {

	}

	void OnTriggerEnter2D(Collider2D collision) {
		string Tag  = collision.gameObject.tag;
		if(Tag =="item0"){
			sources[0].Play();
		}
		if(Tag =="item1"){
			sources[1].Play();
		}
		if(Tag =="item2"){
			sources[2].Play();
		}
		if(Tag =="item3"){
			sources[3].Play();
		}
		if(Tag =="item4"){
			sources[4].Play();
		}
	}

}