using UnityEngine;
using System.Collections;

[RequireComponent(typeof(Renderer))]
public class MaterialChangeTester : MonoBehaviour
{
	private Renderer _renderer;

	void Start ()
	{
		
		_renderer = GetComponent<Renderer>();
		StartCoroutine(BlinkerCoroutine());
	}

	IEnumerator BlinkerCoroutine()
	{
		int rr = Random.Range (1, 4);
		int rg = Random.Range (1, 4);
		int rb = Random.Range (1, 4);
		var originalMaterial = new Material(_renderer.material);
		for (;;)
		{
			float i = 0f;

			while(i<2.0){
			float r = i*1f;
			float g = i*1f;
			float b = i*1f;
			//float r = i*rr*1f;
			//float g = i*rg*1f;
			//float b = i*rb*1f;
			_renderer.material.EnableKeyword ("_EMISSION");
			_renderer.material.SetColor("_EmissionColor", new Color(r, g, b, 1f)); 
			yield return new WaitForSeconds(0.05f); //1秒待って
			i = i + 0.1f;
		}
			while(i>0.0){
				float r = i*1f;
				float g = i*1f;
				float b = i*1f;
				//float r = i*rr*1f;
				//float g = i*rg*1f;
				//float b = i*rb*1f;
				_renderer.material.EnableKeyword ("_EMISSION");
				_renderer.material.SetColor("_EmissionColor", new Color(r, g, b, 1f)); 
				yield return new WaitForSeconds(0.05f); //1秒待って
				i = i - 0.1f;
			}

	}
}
}