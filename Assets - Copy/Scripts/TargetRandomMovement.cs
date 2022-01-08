using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TargetRandomMovement : MonoBehaviour
{
    private float timeToChangeDirection;
    private Rigidbody rigidbody;
    public float moveSpeed;
    public void Start()
    {
        ChangeDirection();
        rigidbody = GetComponent<Rigidbody>();
    }

    // Update is called once per frame
    public void Update()
    {
        timeToChangeDirection -= Time.deltaTime;

        if (timeToChangeDirection <= 0)
        {
            ChangeDirection();
        }

        rigidbody.velocity = transform.forward * moveSpeed;
    }



    private void ChangeDirection()
    {
        float angle = Random.Range(0f, 360f);
        transform.Rotate(0f, angle, 0f, Space.Self);
        timeToChangeDirection = 1.5f;
    }
}
