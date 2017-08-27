using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Player : MonoBehaviour {

	public float flap = 1000f;
	public float scroll = 5f;
	Rigidbody2D rb2d;
	Animator anim;
	bool jump = false;

	void Start () {
		rb2d = GetComponent<Rigidbody2D>();
		anim = GetComponent<Animator>();
	}


	void Update () {

		rb2d.velocity = new Vector2(scroll, rb2d.velocity.y);

		if (Input.GetKeyDown(KeyCode.C) && !Input.GetKeyDown(KeyCode.B) && !jump)
		{
			Jump ();
		}
		if (Input.GetKeyDown(KeyCode.B) && !Input.GetKeyDown(KeyCode.C) && !jump)
		{
			Jump ();
		}
		if (Input.GetKeyDown(KeyCode.B) && Input.GetKeyDown(KeyCode.C) && !jump)
		{
			Jump ();
		}

	}

	void OnCollisionEnter2D(Collision2D other){
		if (other.gameObject.CompareTag("Ground"))
		{
			jump = false;
			anim.SetBool("Ground", true);
		}
	}
	void Jump (){
		jump = true;	
		anim.SetBool("Ground", false);
		rb2d.AddForce(Vector2.up * flap);

	}
}
