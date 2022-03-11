# Room

* pyroomacoustics.room.Room
* pyroomacoustics.soundsource.SoundSource
* pyroomacoustics.beamforming.MicrophoneArray

一个模拟情景中主要包含一个Room、声源、麦克风，然后使用仿真方法在源和麦克风之间创建人造房间脉冲响应（RIR）



脉冲响应是接收到的所有不同脉冲的总和，从直接声音开始，然后是一次反射（源和接收器之间只有一个反射），然后是二次反射（两个壁的反射），等等。

脉冲的延迟是每条路径的延迟，即路径的长度除以声速。每个路径都有一个路径长度，您可以对因该路径长度而延迟的脉冲应用平方反比定律。直接声音仅通过平方反比定律衰减。

平方反比定律和每次反射都会衰减所有反射的声音。您需要了解反射点处壁的材质，以了解衰减量。坚固的抛光大理石墙几乎没有衰减。



Whitted 光线追踪主要解决了场景中没有间接光的问题，但是它解决的也相当的一般，因为它所有的间接光都只来源于完美的镜面反射或者是折射，这种材质显然在现实世界中并不常见，对于大多数的间接光基本无法模拟，这也是由于它对每一个EyeRay 的交点只发出一条的Reflected ray和Refracted ray。这个问题将在分布式光线追踪中有所改善。


