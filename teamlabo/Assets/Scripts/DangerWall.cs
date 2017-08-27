using UnityEngine;
using System.Collections;
using UnityEngine.SceneManagement;

public class DangerWall : MonoBehaviour
{
	void Start(){

	}

	void Update(){

	}

	void OnTriggerEnter2D(Collider2D collision){
		if (collision.gameObject.CompareTag ("Player")) {
			int sceneIndex = SceneManager.GetActiveScene().buildIndex;
			SceneManager.LoadScene(sceneIndex);
		}
	}
}