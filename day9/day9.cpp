#include <iostream>
#include <string>
#include <fstream>
#include <set>
using namespace std;

typedef pair<int,int> pose;

pose move(pose _actual_pose, char dir);
bool is_head_close(pose _h_pose, pose _t_pose);
pose imitate_prev_knot(int dX, int dY);

int main()
{
    // Input file
    ifstream input("input.txt");
    // Coordinates (1st part)
    pose                h_pose          = make_pair(0,0);
    pose                prev_h_pose     = make_pair(0,0);
    pose                t_pose          = make_pair(0,0);
    // Coordinates (2nd part)
    pose                knots_pose[10];
    pose                head_pose_prev;
    // Set of covered coordinates
    set<pose>           covered_poses;
    covered_poses.insert(t_pose);
    // Set of covered coordinates
    set<pose>           covered_poses_2;
    covered_poses_2.insert(knots_pose[9]);

    for(string cmd;getline(input,cmd);)
    {
        // Direction
        char dir  = cmd[0];
        // How many steps will H move? 
        int steps = stoi(cmd.substr(2)); 
        /** 1ST PART **/
        // Now we simulate motion step by step (1st part)
        for(int step=0;step<steps;step++)
        {
            prev_h_pose = h_pose;
            h_pose      = move(h_pose,dir);
            if(!is_head_close(h_pose,t_pose))
                t_pose = prev_h_pose;
            covered_poses.insert(t_pose);
        }
        /** 2ND PART **/
        // Now we simulate motion step by step (2nd part)
        for(int step=0;step<steps;step++)
        {
            head_pose_prev      = knots_pose[0];
            knots_pose[0]       = move(knots_pose[0],dir);
            // 1st knot follows the head.
            if(!is_head_close(knots_pose[0],knots_pose[1]))
                knots_pose[1] = head_pose_prev;
            // From 2 to 9 the motion is "different"
            for(int i=0;i<9;i++)
            {
                if(!is_head_close(knots_pose[i],knots_pose[i+1]))
                {
                    int dX  = knots_pose[i].first   - knots_pose[i+1].first;
                    int dY  = knots_pose[i].second  - knots_pose[i+1].second;
                    knots_pose[i+1].first           += imitate_prev_knot(dX,dY).first;
                    knots_pose[i+1].second          += imitate_prev_knot(dX,dY).second;
                }
                covered_poses_2.insert(knots_pose[9]);
            }
        }
    }
    cout<<"1st Part solution is: "<<covered_poses.size()<<endl;
    cout<<"2nd Part solution is: "<<covered_poses_2.size()<<endl;
    return 0;
}

pose move(pose _actual_pose, char _dir)
{
    pose new_pose = _actual_pose;
    switch (_dir)
    {
    case 'R':
        new_pose.first++;
        break;
    case 'L':
        new_pose.first--;
        break;
    case 'U':
        new_pose.second++;
        break;
    case 'D':
        new_pose.second--;
        break;
    }
    return new_pose;
}

bool is_head_close(pose _h_pose, pose _t_pose)
{
    return !(abs(_h_pose.first-_t_pose.first)>=2 || abs(_h_pose.second-_t_pose.second)>=2);   
}

pose imitate_prev_knot(int dX, int dY)
{
    if(abs(dX)==2)
        dX = dX/2;
    if(abs(dY)==2)
        dY = dY/2;
    return make_pair(dX,dY);
}
