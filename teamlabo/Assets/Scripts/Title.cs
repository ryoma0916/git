using UnityEngine;
using System.Collections;
using UnityEngine.UI;
using UnityEngine.EventSystems;
using UnityEngine.SceneManagement;

[RequireComponent(typeof(Button))]
public class  Title: UIBehaviour
{
	protected override void Start(){
		base.Start();
		GetComponent<Button>().onClick.AddListener(OnClick);
		}

	void OnClick(){
		SceneManager.LoadScene("1");
		}
}