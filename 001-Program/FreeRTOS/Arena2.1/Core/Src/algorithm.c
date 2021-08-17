//
// Created by dream on 2021/6/12.
//

#include "algorithm.h"

/*
 * 引用的外部文件结构体-------------------------------------------------------------------------------------
 */
extern Sensor_TypeDef sensors;
extern Motor_TypeDef motor;

/*
 * 小函数-------------------------------------------------------------------------------------
 * 虽然部分小函数库里有，为避免某些数据类型出差错，将某一部分函数重写
*/
uint32_t my_32abs(uint32_t number) {
    return number > 0 ? number : (-number);
}

int my_abs(int number) {
    return number > 0 ? number : (-number);
}

/*
 * 一阶低通滤波函数-------------------------------------------------------------------------------------
 */
/**
 * @简 介： 一阶低通滤波函数
 * @参 数： alpha系数，当前值，上次计数
 * @返回值： 滤波后参数
 */
float filter(float alpha, float adc_now, float adc_pre) {
    return alpha * adc_now + (1 - alpha) * adc_pre;
}


/*
 * 快速排序算法-------------------------------------------------------------------------------------
 */
/**
 * @简 介： 快速排序实现
 * @参 数： 待排序的数组，数组长度
 * @返回值： 无
 */
void quick_sort(int a[], int length) {
    my_qsort(a, 0, length - 1);
}

/**
 * @简 介： 快排算法的递归实现
 * @参 数： 待排序数组，数组索引低值，数组索引高值
 * @返回值： 无
 * @备 注：内部函数，外部无需调用
 */
void my_qsort(int a[], int low, int high) {
    if (low < high) {
        int t = partition(a, low, high);
        my_qsort(a, low, t - 1);
        my_qsort(a, t + 1, high);
    }
}

/**
 * @简 介： 快排算法的分组实现
 * @参 数： 已分好的数组，数组索引低值，数组索引高值
 * @返回值： 数组索引低值
 * @备 注：内部函数，外部无需调用
 */
int partition(int a[], int low, int high) {
    int t = a[low];
    while (low < high) {
        while (low < high && a[high] >= t) {
            high--;
        }
        a[low] = a[high];
        while (low < high && a[low] <= t) {
            low++;
        }
        a[high] = a[low];
    }
    a[low] = t;
    return low;
}

/**
 * @简 介： 方向判断函数
 * @参 数： 传入数组为按前后左右顺序排布的四向传感器数据
 * @返回值： 返回当下哪个方向上可能有敌人
 * @备 注：无
 */
int direction_judge(int a[]) {
    int length = sizeof(a);
    int range[length];
    int range_flag[length];

    for (int i = 0; i < length; ++i) {
        range[i] = a[i];
        range_flag[i] = a[i];
    }

    quick_sort(range, length);

    if (range[(length - 1)] > 1100) {

        if (range[(length - 1)] == range_flag[0]) {

            return forward;
        } else if (range[(length - 1)] == range_flag[1]) {

            return backward;
        } else if (range[(length - 1)] == range_flag[2]) {

            return left;
        } else if (range[(length - 1)] == range_flag[3]) {

            return right;
        }
    }
    return wait;
}

/*
 * 变权重均值计算-------------------------------------------------------------------------------------
 */

/**
 * @简 介： 变权重均值计算
 * @参 数： 以数组形式传入左右传感器数值
 * @返回值： 经变权重取得的均值
 * @备 注：其实这个函数作用并不大，理论上来说直接取其中最大值作为前侧传感器即可
 *        但作为多传感器数据的融合，与达到细微控制的实现，还应根据var_weight
 *        去判断前侧目标偏移值，由于武术擂台项目对其控制精度要求不高，所以后期
 *        可能会用，所以前期做些准备
 */
int varweight_mean(int a[]) {
    int mean;
    int diff;
    double left_weight = 0.50;
    double right_weight = 0.50;

    int left_value, right_value;

    //这个差值权重很重要，需要将diff映射到0-0.5，后面就不需要加限幅函数
    //或将diff后的变化差值限定最高阈值，保证最终转化值达到判断条件即可
    //估计diffmax=3800-800=3000，实测：diffmax=2400
    double var_weight = 0.0002;

    //这里最好养成习惯，传入的数组先复制再使用，避免某些地方修改原数据
    left_value = a[0];
    right_value = a[1];

//    经测试，diff经常有溢出现象，故应过滤处理
//    溢出是由于使用uint ，以后应注意，在encode上也出现过类似问题
    diff = limit_range((left_value - right_value), 4000);

//   这里加一条判断条件，相差太小可不做权重分析
    if (my_abs(diff) > 200) {
//        diff为代数值，故权重可增可减
        left_weight += diff * var_weight;
//        这里为避免weight相差太多，导致灵敏性差
//        或总和超过1引起的后续标志判断出错，使用作差确定另一半权重值
//        right_weight = right_weight - diff * var_weight;
        right_weight = 1 - left_weight;
    }

    mean = (int) (left_value * left_weight + right_value * right_weight);

    left_weight = 0.5;
    right_weight = 0.5;

    return mean;
}


/*
 * 角度控制算法-------------------------------------------------------------------------------------
 */
/**
 * @简 介： 角度绝对值控制函数
 * @参 数： 目标角度值，顺时针为正，逆时针为负
 * @返回值： 是否已到达目标角度
 * @备 注：无
 */
int angle_position(int TargetAngle) {
    //将角度值映射到0-65535
    //其实这个映射为0-65535或0-360是一样的，只是较大的数值会提高一点控制精度
    int TargetValue = TargetAngle * 182;    //182=(1/360)*65535
    int bias;
    int sum = 0;
    HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);

    while (1) {
        bias = Get_Bias(sensors.YAW, TargetValue);
        sum += bias;

        motor_control(-bias * motor.turn_coff, bias * motor.turn_coff);
        HAL_Delay(1);
        if (my_abs(bias) < 600) {
            break;
        }
    }

    motor_control(0, 0);
}

/**
 * @简 介： 角度增量式控制函数
 * @参 数： 增量式目标角度值，顺时针为正，逆时针为负
 * @返回值： 是否已到达目标角度
 * @备 注： 无
 */
int angle_incremental(int deviation) {
    int target;
    int bias;
    int sum = 0;
    int deviationValue = deviation * 182;//182=(1/360)*65535
    int local_angle = sensors.YAW;

    target = Get_Target(local_angle, deviationValue);
//    motor.target = 32000;

    HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);

    while (1) {
        bias = Get_Bias(sensors.YAW, target);
        sum += bias;
        motor_control(-bias * motor.turn_coff, bias * motor.turn_coff);
        HAL_Delay(1);
        if (my_abs(bias) < 600) {
            break;
        }
    }
    motor_control(0, 0);
}


int Get_Target(int start, int bias) {

    int sum = start + bias;

    if (sum < 0) {
        sum += 65535;
    } else if (sum > 65535) {
        sum -= 65535;
    } else {
        return sum;
    }
}

int Get_Bias(int start, int target) {
    int bias;
    bias = target - start;
    if (bias < -32000) {
        bias = bias + 65535;
    } else if (bias > 32000) {
        bias = bias - 65535;
    }
    return bias;
}


/*
 * PID控制器-------------------------------------------------------------------------------------
 */
int PID_Control(int SetPoint, int CurrentPoint, PID_TypeDef pid_params) {
    int result;

    pid_params.LastError = CurrentPoint - SetPoint;
    pid_params.SumError += pid_params.LastError;

    result = pid_params.LastError * pid_params.Proportion +
             pid_params.SumError * pid_params.Integral +
             (pid_params.LastError - pid_params.PrevError) * pid_params.Derivative;

    pid_params.PrevError = pid_params.LastError;

    return result;
}












