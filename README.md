# UE5 简单角色攀爬系统实现

## 简要总结

1.Mixamo动画资产 --> Mixamo Converter --> 能够拖入到UE5正确使用的动画资产

2.利用Control Rig在虚幻引擎里调整动画（如Root的Transform）：动画序列 --> 在Sequencer中编辑 --> 烘焙到控制绑定(Control Rig) --> 在Map中进行动画编辑 --> 在Control Rig节点中进行攀爬手部吸附IK等细节处理

3.利用UE5新特性Motion Warping实现对不同形状的障碍物的动画扭曲

4.对于攀爬系统，其总体实现方式是通过不同高度的射线/碰撞检测来执行不同情况下的动作，具体拆分图如下：

5.对于手部/脚步贴近墙壁细节处理，可利用FullBody IK

6.对UE5的增强输入系统(EnhancedInput)的使用

## 一些笔记

### Control Rig

* **Control Rig**、**Sequencer**、**Anim Sequence**之间的关系与区别？

**Control Rig** 是一套基于蓝图的、实时的绑定系统，用于实现在引擎中直接为角色添加动画，或者修改动画  
**Sequencer** 是虚幻引擎对场景动画的一个组织器  
**Anim Sequence** 是动画序列，是由美术师创造的美术资产  

* **Control Rig** 与 **动画蓝图** 之间的区别与联系

区别： 在概念上，**动画蓝图** 是用于控制动画的逻辑脚本；而 **Control Rig** 中的Rig Graph则是用来约束骨骼的脚本。  
所以，**动画蓝图** 更像是动画的Controller，而 **Control Rig** 则是Component，是一个功能的载体。

联系： 可以在 **动画蓝图** 中利用 **Control Rig** 节点，在Control Rig节点内部绑定一些逻辑（如IK等），然后暴露接口给动画蓝图业务层使用。

### Root Motion

0. 启用根骨骼动画(Root Motion)，可以用动画数据驱动角色动作，从而实现更真实的动作。  
网格体骨架驱动动画 --> 骨骼组成骨架 --> 根骨骼(Root Bone)是所有骨骼的基础参考
根骨骼上的运动数据默认情况下不会影响角色运动，必须启用**Root Motion**才能影响动作。

### Motion Warping

官方： **Motion Warping** 是一种可以动态调整角色的根骨骼运动以对齐目标的功能
其他： MotionWarping（运动扭曲）可对角色根运动进行修改，从而让角色根运动动画结束时准确停在某一点（这个点就是Warp Target）。使用该功能后，对于翻越障碍物这类原先需要禁用根运动用代码做位移的操作，将变得简便。

1. 要使用Motion Warping，需要在Plugin启用
2. 在动画蒙太奇中，选择一个轨道添加Anim Notify State --> Motion Warping（需要原动画序列启用Root Motion）
3. 将 **根骨骼运动修饰符配置（Root Motion Modifier Config）** 设置为 倾斜（Skew）扭曲（Warp）** 。此操作用于指定扭曲类型。（此项目中，用于跨越障碍物）
4. 为 扭曲目标名称（Warp Target Name） 设置名称。此操作用于用名称标识此扭曲。
5. 在蓝图中添加Motion Warping组件，通过C++代码或蓝图调用Add or Update Warp Target From Transform并播放该蒙太奇
