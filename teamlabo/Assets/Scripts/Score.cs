using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class Score : MonoBehaviour {

	private int score = 10;

	void Start () {
		GetComponent<Text>().text = "Life: " + score.ToString();
	}

	public void Damage (int point)
	{
		score += point;
		GetComponent<Text> ().text = "Life: " + score.ToString ();
	}
}