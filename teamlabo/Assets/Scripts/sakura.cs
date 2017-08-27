
using UnityEngine;
using System.Collections;

public class sakura : MonoBehaviour {

	public GameObject player;
	public Vector3 offset;

	void Start () {
		offset = transform.position - player.transform.position;
	}

	void LateUpdate () {
		Vector3 newPosition = transform.position;
		newPosition.x = player.transform.position.x + offset.x;
		newPosition.y = offset.y;
		newPosition.z = player.transform.position.z + offset.z;
		transform.position = newPosition;
	}
}