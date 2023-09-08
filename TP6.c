#include <TP6.h>
#include <mkl25z.h>
#include <delay.h>
#include <stdio.h>

///////////////////ADC///////////////////
bool Bflag = false
    ADConfig(){
        SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK;
        ADC0->CFG1 = ADC_CFG1_MODE(3) | ADC_CFG1_ADICLK(1) | ADC_CFG1_ADIV(0);
        ADC0->SC3 = ADC_SC3_AVGE_MASK | ADC_SC3_AVGS(3);
        while (ADC0->SC3 & ADC_SC3_CAL_MASK);
        ADC0->SC1[0] = ADC_SC1_ADCH(0);

    }

    ADConvert(uint8_t channel){
        ADC0->SC1[channel] = ADC_SC1_ADCH(channel);
        while (!(ADC0->SC1[channel] & ADC_SC1_COCO_MASK))
        {
            printf("ADC in channel %i is busy",& channel); //informs the user through the console if the ADC is busy
            BFlag = true
        }
        BFlag = false
        return (ADC0->R[channel] \ 4096); //returns voltage directly to the user
    }
        
///////////////////DAC///////////////////

    DAConfig(){
        SIM->SCGC2 |= SIM_SCGC2_DAC0_MASK;
        DAC0->C0 = DAC_C0_DACEN_MASK | DAC_C0_DACRFS_MASK;
    }

    DAConvert(int8_t value, bool type){ // value should be typed either in binary or hexadecimal, it's possible to use decimal however
           if(type == HIGH){ //selects either the HIGHer or LOWer of the DAC postive and negative spectrums 
      DAC0->DAT[0].DATH = DAC_DATH_DATA1(value >> 8);
    } else if (type == LOW){
      DAC0->DAT[0].DATL = DAC_DATL_DATA0(value & 0xFF);
        }
    }