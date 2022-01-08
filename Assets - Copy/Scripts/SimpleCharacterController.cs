using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SimpleCharacterController : MonoBehaviour
{
    public float moveSpeed = 2f;

    public float turnSpeed = 300;

    public bool allowJump;

    public float jumpSpeed = 4f;

    public bool isGrounded;

    public Transform IsGroundedTransform;
    public float ForwardInput { get; set; }
    public float TurnInput { get; set; }
    public bool JumpInput { get; set; }

    new private Rigidbody rigidbody;
    private CapsuleCollider capsuleCollider;
    public LayerMask playerMask;

    private void Awake()
    {
        rigidbody = GetComponent<Rigidbody>();
        capsuleCollider = GetComponent<CapsuleCollider>();
    }

    private void FixedUpdate()
    {
        CheckGrounded();
        ProcessActions();
    }

    private void CheckGrounded()
    {
        isGrounded = true;
        if(Physics.OverlapSphere(IsGroundedTransform.position, 0.1f, playerMask).Length==0)
        {
            isGrounded = false;
        }
    }

    private void ProcessActions()
    {
        // Turning
        if (TurnInput!=0f)
        {
            float angle = Mathf.Clamp(TurnInput, -1f, 1f) * turnSpeed;
            transform.Rotate(Vector3.up, Time.fixedDeltaTime * angle);
        }

        Vector3 move = transform.forward * Mathf.Clamp(ForwardInput, -1f, 1f) *
            moveSpeed * Time.fixedDeltaTime;
        rigidbody.MovePosition(transform.position + move);

        // Jump
        if (JumpInput && allowJump && isGrounded)
        {
            rigidbody.AddForce(transform.up * jumpSpeed, ForceMode.VelocityChange);
        }
    }
}
