粗略总结学习到的点：
1.Mixamo动画资产 --> Mixamo Converter --> 能够拖入到UE5正确使用的动画资产
2.利用Control Rig在虚幻引擎里调整动画（如Root的Transform）
3.利用UE5新特性Motion Warping实现对不同形状的障碍物的动画扭曲
4.对于攀爬系统，其总体实现方式是通过不同高度的射线/碰撞检测来执行不同情况下的动作，具体拆分图如下：
5.对于手部/脚步贴近墙壁细节处理，可利用FullBody IK
6.对UE5的增强输入系统(EnhancedInput)的使用
