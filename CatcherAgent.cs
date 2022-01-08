using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Unity.MLAgents;
using Unity.MLAgents.Actuators;


public class CatcherAgent : Agent
{
    public GameObject gate;

    private Vector3 startPosition;
    private SimpleCharacterController characterController;
    new private Rigidbody rigidbody;

    //Called when the agent is initialized
    public override void Initialize()
    {
        startPosition = transform.position;
        characterController = GetComponent<SimpleCharacterController>();
        rigidbody = GetComponent<Rigidbody>();
    }

    public override void OnEpisodeBegin()
    {
        // Reset agent position, rotation
        transform.position = Vector3.forward * Random.Range(-9f, 9f) + Vector3.right * Random.Range(-4f, 0f)+Vector3.up;
        transform.rotation = Quaternion.Euler(Vector3.up * Random.Range(0f, 360f));
        rigidbody.velocity = Vector3.zero;

        //reset position of the gate
        gate.transform.position = new Vector3(-10.5f, 0.5f, -5f);
        gate.transform.rotation = Quaternion.Euler(Vector3.zero);

    }

    public override void Heuristic(in ActionBuffers actionsOut)
    {
        // Read input values and round them. GetAxisRaw works better in this case
        // because of the DecisionRequester, which only gets new decisions periodically.
        int vertical = Mathf.RoundToInt(Input.GetAxisRaw("Vertical"));
        int horizontal = Mathf.RoundToInt(Input.GetAxisRaw("Horizontal"));
        bool jump = Input.GetKey(KeyCode.Space);

        // Convert the actions to Discrete choices (0, 1, 2)
        ActionSegment<int> actions = actionsOut.DiscreteActions;
        actions[0] = vertical >= 0 ? vertical : 2;
        actions[1] = horizontal >= 0 ? horizontal : 2;
        actions[2] = jump ? 1 : 0;
    }

    public override void OnActionReceived(ActionBuffers actions)
    {   
        if (StepCount==MaxStep)
        {
            AddReward(-1f);
        }
        // Punish and end episode if the agent goes off the map
        if (transform.position[0] > 5.5f || transform.position[0] < -16.5f || transform.position[2] > 10f || transform.position[2] < -10f)
        {
            AddReward(-1f);
            EndEpisode();
        }

        // Convert actions from Discrete (0, 1, 2) to expected input values (-1, 0, +1)
        // of the character controller
        float vertical = actions.DiscreteActions[0] <= 1 ? actions.DiscreteActions[0] : -1;
        float horizontal = actions.DiscreteActions[1] <= 1 ? actions.DiscreteActions[1] : -1;
        bool jump = actions.DiscreteActions[2] > 0;

        characterController.ForwardInput = vertical;
        characterController.TurnInput = horizontal;
        characterController.JumpInput = jump;
    }

    private void OnTriggerEnter(Collider other)
    {
        // If the other object is a target, reward and end episode
        if (other.tag == "target")
        {
            AddReward(1f);
            EndEpisode();
        }
    }

}
