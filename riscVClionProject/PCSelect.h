//
// Created by Глеб Уваркин on 2019-12-09.
//

#ifndef TACTICMODEL_PCSELECT_H
#define TACTICMODEL_PCSELECT_H


class PCSelect {
public:
    unsigned int branch;
    unsigned int jabs;
    unsigned int rind;
    unsigned int PCplus4;

    unsigned int select = 0;
    unsigned int getPC();
    void setPCplus4(unsigned int pc);
    void setBranch(unsigned int pc);
    void setJabs(unsigned int pc);
    void setRind(unsigned int pc);

};


#endif //TACTICMODEL_PCSELECT_H
