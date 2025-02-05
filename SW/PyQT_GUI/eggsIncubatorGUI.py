# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'eggsIncubatorGUI.ui'
#
# Created by: PyQt5 UI code generator 5.15.10
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(640, 480)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.tabWidget = QtWidgets.QTabWidget(self.centralwidget)
        self.tabWidget.setEnabled(True)
        self.tabWidget.setGeometry(QtCore.QRect(0, 0, 651, 441))
        self.tabWidget.setObjectName("tabWidget")
        self.mainView_tab = QtWidgets.QWidget()
        self.mainView_tab.setObjectName("mainView_tab")
        self.groupBox_3 = QtWidgets.QGroupBox(self.mainView_tab)
        self.groupBox_3.setGeometry(QtCore.QRect(0, 0, 161, 161))
        self.groupBox_3.setObjectName("groupBox_3")
        self.widget_2 = QtWidgets.QWidget(self.groupBox_3)
        self.widget_2.setGeometry(QtCore.QRect(0, 20, 161, 141))
        self.widget_2.setObjectName("widget_2")
        self.layoutWidget = QtWidgets.QWidget(self.widget_2)
        self.layoutWidget.setGeometry(QtCore.QRect(9, 9, 141, 121))
        self.layoutWidget.setObjectName("layoutWidget")
        self.gridLayout_5 = QtWidgets.QGridLayout(self.layoutWidget)
        self.gridLayout_5.setContentsMargins(0, 0, 0, 0)
        self.gridLayout_5.setObjectName("gridLayout_5")
        self.T3_T = QtWidgets.QLabel(self.layoutWidget)
        self.T3_T.setObjectName("T3_T")
        self.gridLayout_5.addWidget(self.T3_T, 2, 0, 1, 1)
        self.T1_T = QtWidgets.QLabel(self.layoutWidget)
        self.T1_T.setObjectName("T1_T")
        self.gridLayout_5.addWidget(self.T1_T, 0, 0, 1, 1)
        self.T4_T = QtWidgets.QLabel(self.layoutWidget)
        self.T4_T.setObjectName("T4_T")
        self.gridLayout_5.addWidget(self.T4_T, 3, 0, 1, 1)
        self.temperature4_T = QtWidgets.QLabel(self.layoutWidget)
        self.temperature4_T.setObjectName("temperature4_T")
        self.gridLayout_5.addWidget(self.temperature4_T, 3, 1, 1, 1)
        self.temperature3_T = QtWidgets.QLabel(self.layoutWidget)
        self.temperature3_T.setObjectName("temperature3_T")
        self.gridLayout_5.addWidget(self.temperature3_T, 2, 1, 1, 1)
        self.temperature1_T = QtWidgets.QLabel(self.layoutWidget)
        self.temperature1_T.setObjectName("temperature1_T")
        self.gridLayout_5.addWidget(self.temperature1_T, 0, 1, 1, 1)
        self.temperature2_T = QtWidgets.QLabel(self.layoutWidget)
        self.temperature2_T.setObjectName("temperature2_T")
        self.gridLayout_5.addWidget(self.temperature2_T, 1, 1, 1, 1)
        self.T2_T = QtWidgets.QLabel(self.layoutWidget)
        self.T2_T.setObjectName("T2_T")
        self.gridLayout_5.addWidget(self.T2_T, 1, 0, 1, 1)
        self.groupBox_4 = QtWidgets.QGroupBox(self.mainView_tab)
        self.groupBox_4.setGeometry(QtCore.QRect(170, 0, 121, 161))
        self.groupBox_4.setObjectName("groupBox_4")
        self.layoutWidget_4 = QtWidgets.QWidget(self.groupBox_4)
        self.layoutWidget_4.setGeometry(QtCore.QRect(0, 30, 114, 21))
        self.layoutWidget_4.setObjectName("layoutWidget_4")
        self.horizontalLayout_2 = QtWidgets.QHBoxLayout(self.layoutWidget_4)
        self.horizontalLayout_2.setContentsMargins(0, 0, 0, 0)
        self.horizontalLayout_2.setObjectName("horizontalLayout_2")
        self.H1_H = QtWidgets.QLabel(self.layoutWidget_4)
        self.H1_H.setObjectName("H1_H")
        self.horizontalLayout_2.addWidget(self.H1_H)
        self.humidity1_H = QtWidgets.QLabel(self.layoutWidget_4)
        self.humidity1_H.setObjectName("humidity1_H")
        self.horizontalLayout_2.addWidget(self.humidity1_H)
        self.groupBox_5 = QtWidgets.QGroupBox(self.mainView_tab)
        self.groupBox_5.setGeometry(QtCore.QRect(300, 0, 271, 161))
        self.groupBox_5.setObjectName("groupBox_5")
        self.layoutWidget_3 = QtWidgets.QWidget(self.groupBox_5)
        self.layoutWidget_3.setGeometry(QtCore.QRect(0, 30, 181, 91))
        self.layoutWidget_3.setObjectName("layoutWidget_3")
        self.gridLayout_6 = QtWidgets.QGridLayout(self.layoutWidget_3)
        self.gridLayout_6.setContentsMargins(0, 0, 0, 0)
        self.gridLayout_6.setObjectName("gridLayout_6")
        self.maxValue_lineEdit = QtWidgets.QLineEdit(self.layoutWidget_3)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Minimum, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.maxValue_lineEdit.sizePolicy().hasHeightForWidth())
        self.maxValue_lineEdit.setSizePolicy(sizePolicy)
        self.maxValue_lineEdit.setObjectName("maxValue_lineEdit")
        self.gridLayout_6.addWidget(self.maxValue_lineEdit, 1, 0, 1, 1)
        self.maxHysteresisValue_temperature_spinBox = QtWidgets.QDoubleSpinBox(self.layoutWidget_3)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.maxHysteresisValue_temperature_spinBox.sizePolicy().hasHeightForWidth())
        self.maxHysteresisValue_temperature_spinBox.setSizePolicy(sizePolicy)
        self.maxHysteresisValue_temperature_spinBox.setMinimum(15.0)
        self.maxHysteresisValue_temperature_spinBox.setMaximum(40.0)
        self.maxHysteresisValue_temperature_spinBox.setSingleStep(0.1)
        self.maxHysteresisValue_temperature_spinBox.setProperty("value", 37.8)
        self.maxHysteresisValue_temperature_spinBox.setObjectName("maxHysteresisValue_temperature_spinBox")
        self.gridLayout_6.addWidget(self.maxHysteresisValue_temperature_spinBox, 1, 1, 1, 1)
        self.minHysteresisValue_temperature_spinBox = QtWidgets.QDoubleSpinBox(self.layoutWidget_3)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.minHysteresisValue_temperature_spinBox.sizePolicy().hasHeightForWidth())
        self.minHysteresisValue_temperature_spinBox.setSizePolicy(sizePolicy)
        self.minHysteresisValue_temperature_spinBox.setMinimum(15.0)
        self.minHysteresisValue_temperature_spinBox.setMaximum(40.0)
        self.minHysteresisValue_temperature_spinBox.setSingleStep(0.1)
        self.minHysteresisValue_temperature_spinBox.setProperty("value", 37.5)
        self.minHysteresisValue_temperature_spinBox.setObjectName("minHysteresisValue_temperature_spinBox")
        self.gridLayout_6.addWidget(self.minHysteresisValue_temperature_spinBox, 2, 1, 1, 1)
        self.minValue_lineEdit = QtWidgets.QLineEdit(self.layoutWidget_3)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Minimum, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.minValue_lineEdit.sizePolicy().hasHeightForWidth())
        self.minValue_lineEdit.setSizePolicy(sizePolicy)
        self.minValue_lineEdit.setObjectName("minValue_lineEdit")
        self.gridLayout_6.addWidget(self.minValue_lineEdit, 2, 0, 1, 1)
        self.Heater = QtWidgets.QLabel(self.layoutWidget_3)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Minimum, QtWidgets.QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.Heater.sizePolicy().hasHeightForWidth())
        self.Heater.setSizePolicy(sizePolicy)
        self.Heater.setObjectName("Heater")
        self.gridLayout_6.addWidget(self.Heater, 3, 0, 1, 1)
        self.heaterStatus = QtWidgets.QLabel(self.layoutWidget_3)
        self.heaterStatus.setObjectName("heaterStatus")
        self.gridLayout_6.addWidget(self.heaterStatus, 3, 1, 1, 1)
        self.groupBox_6 = QtWidgets.QGroupBox(self.mainView_tab)
        self.groupBox_6.setGeometry(QtCore.QRect(300, 170, 291, 191))
        self.groupBox_6.setObjectName("groupBox_6")
        self.move_CW_motor_btn = QtWidgets.QPushButton(self.groupBox_6)
        self.move_CW_motor_btn.setGeometry(QtCore.QRect(140, 30, 121, 27))
        self.move_CW_motor_btn.setObjectName("move_CW_motor_btn")
        self.move_CCW_motor_btn = QtWidgets.QPushButton(self.groupBox_6)
        self.move_CCW_motor_btn.setGeometry(QtCore.QRect(10, 30, 121, 27))
        self.move_CCW_motor_btn.setObjectName("move_CCW_motor_btn")
        self.forceEggsTurn_motor_btn = QtWidgets.QPushButton(self.groupBox_6)
        self.forceEggsTurn_motor_btn.setGeometry(QtCore.QRect(140, 70, 121, 27))
        self.forceEggsTurn_motor_btn.setObjectName("forceEggsTurn_motor_btn")
        self.reset_motor_btn = QtWidgets.QPushButton(self.groupBox_6)
        self.reset_motor_btn.setGeometry(QtCore.QRect(180, 110, 88, 27))
        self.reset_motor_btn.setObjectName("reset_motor_btn")
        self.layHorizontal_motor_btn = QtWidgets.QPushButton(self.groupBox_6)
        self.layHorizontal_motor_btn.setGeometry(QtCore.QRect(10, 70, 121, 27))
        self.layHorizontal_motor_btn.setObjectName("layHorizontal_motor_btn")
        self.layoutWidget_5 = QtWidgets.QWidget(self.groupBox_6)
        self.layoutWidget_5.setGeometry(QtCore.QRect(10, 110, 155, 30))
        self.layoutWidget_5.setObjectName("layoutWidget_5")
        self.horizontalLayout = QtWidgets.QHBoxLayout(self.layoutWidget_5)
        self.horizontalLayout.setContentsMargins(0, 0, 0, 0)
        self.horizontalLayout.setObjectName("horizontalLayout")
        self.label = QtWidgets.QLabel(self.layoutWidget_5)
        self.label.setObjectName("label")
        self.horizontalLayout.addWidget(self.label)
        self.speedRPM_motor_spinBox = QtWidgets.QDoubleSpinBox(self.layoutWidget_5)
        self.speedRPM_motor_spinBox.setDecimals(1)
        self.speedRPM_motor_spinBox.setSingleStep(0.5)
        self.speedRPM_motor_spinBox.setProperty("value", 5.0)
        self.speedRPM_motor_spinBox.setObjectName("speedRPM_motor_spinBox")
        self.horizontalLayout.addWidget(self.speedRPM_motor_spinBox)
        self.widget = QtWidgets.QWidget(self.groupBox_6)
        self.widget.setGeometry(QtCore.QRect(10, 160, 185, 21))
        self.widget.setObjectName("widget")
        self.horizontalLayout_3 = QtWidgets.QHBoxLayout(self.widget)
        self.horizontalLayout_3.setContentsMargins(0, 0, 0, 0)
        self.horizontalLayout_3.setObjectName("horizontalLayout_3")
        self.Motor_Status = QtWidgets.QLabel(self.widget)
        self.Motor_Status.setObjectName("Motor_Status")
        self.horizontalLayout_3.addWidget(self.Motor_Status)
        self.motorStatus = QtWidgets.QLabel(self.widget)
        self.motorStatus.setObjectName("motorStatus")
        self.horizontalLayout_3.addWidget(self.motorStatus)
        self.groupBox_7 = QtWidgets.QGroupBox(self.mainView_tab)
        self.groupBox_7.setGeometry(QtCore.QRect(10, 180, 161, 131))
        self.groupBox_7.setObjectName("groupBox_7")
        self.widget1 = QtWidgets.QWidget(self.groupBox_7)
        self.widget1.setGeometry(QtCore.QRect(0, 30, 115, 89))
        self.widget1.setObjectName("widget1")
        self.verticalLayout = QtWidgets.QVBoxLayout(self.widget1)
        self.verticalLayout.setContentsMargins(0, 0, 0, 0)
        self.verticalLayout.setObjectName("verticalLayout")
        self.heaterOFF_radioBtn = QtWidgets.QRadioButton(self.widget1)
        self.heaterOFF_radioBtn.setObjectName("heaterOFF_radioBtn")
        self.overwriteCommands_radioButtonGroup = QtWidgets.QButtonGroup(MainWindow)
        self.overwriteCommands_radioButtonGroup.setObjectName("overwriteCommands_radioButtonGroup")
        self.overwriteCommands_radioButtonGroup.addButton(self.heaterOFF_radioBtn)
        self.verticalLayout.addWidget(self.heaterOFF_radioBtn)
        self.heaterAUTO_radioBtn = QtWidgets.QRadioButton(self.widget1)
        self.heaterAUTO_radioBtn.setObjectName("heaterAUTO_radioBtn")
        self.overwriteCommands_radioButtonGroup.addButton(self.heaterAUTO_radioBtn)
        self.verticalLayout.addWidget(self.heaterAUTO_radioBtn)
        self.heaterON_radioBtn = QtWidgets.QRadioButton(self.widget1)
        self.heaterON_radioBtn.setObjectName("heaterON_radioBtn")
        self.overwriteCommands_radioButtonGroup.addButton(self.heaterON_radioBtn)
        self.verticalLayout.addWidget(self.heaterON_radioBtn)
        self.tabWidget.addTab(self.mainView_tab, "")
        self.statistics_tab = QtWidgets.QWidget()
        self.statistics_tab.setObjectName("statistics_tab")
        self.groupBox_8 = QtWidgets.QGroupBox(self.statistics_tab)
        self.groupBox_8.setGeometry(QtCore.QRect(0, 0, 631, 191))
        self.groupBox_8.setObjectName("groupBox_8")
        self.reset_statistics_T_btn = QtWidgets.QPushButton(self.groupBox_8)
        self.reset_statistics_T_btn.setGeometry(QtCore.QRect(540, 20, 91, 31))
        self.reset_statistics_T_btn.setObjectName("reset_statistics_T_btn")
        self.layoutWidget1 = QtWidgets.QWidget(self.groupBox_8)
        self.layoutWidget1.setGeometry(QtCore.QRect(10, 30, 446, 21))
        self.layoutWidget1.setObjectName("layoutWidget1")
        self.gridLayout = QtWidgets.QGridLayout(self.layoutWidget1)
        self.gridLayout.setContentsMargins(0, 0, 0, 0)
        self.gridLayout.setObjectName("gridLayout")
        self.Min_T = QtWidgets.QLabel(self.layoutWidget1)
        self.Min_T.setObjectName("Min_T")
        self.gridLayout.addWidget(self.Min_T, 0, 0, 1, 1, QtCore.Qt.AlignRight)
        self.minTemp_T = QtWidgets.QLabel(self.layoutWidget1)
        self.minTemp_T.setObjectName("minTemp_T")
        self.gridLayout.addWidget(self.minTemp_T, 0, 1, 1, 1)
        self.Mean_T = QtWidgets.QLabel(self.layoutWidget1)
        self.Mean_T.setObjectName("Mean_T")
        self.gridLayout.addWidget(self.Mean_T, 0, 2, 1, 1, QtCore.Qt.AlignRight)
        self.meanTemp_T = QtWidgets.QLabel(self.layoutWidget1)
        self.meanTemp_T.setObjectName("meanTemp_T")
        self.gridLayout.addWidget(self.meanTemp_T, 0, 3, 1, 1)
        self.Max_T = QtWidgets.QLabel(self.layoutWidget1)
        self.Max_T.setObjectName("Max_T")
        self.gridLayout.addWidget(self.Max_T, 0, 4, 1, 1, QtCore.Qt.AlignRight)
        self.maxTemp_T = QtWidgets.QLabel(self.layoutWidget1)
        self.maxTemp_T.setObjectName("maxTemp_T")
        self.gridLayout.addWidget(self.maxTemp_T, 0, 5, 1, 1)
        self.plotAllDays_cnt_T_btn = QtWidgets.QPushButton(self.groupBox_8)
        self.plotAllDays_cnt_T_btn.setGeometry(QtCore.QRect(340, 60, 121, 31))
        self.plotAllDays_cnt_T_btn.setObjectName("plotAllDays_cnt_T_btn")
        self.plotToday_cnt_T_btn = QtWidgets.QPushButton(self.groupBox_8)
        self.plotToday_cnt_T_btn.setGeometry(QtCore.QRect(470, 60, 121, 31))
        self.plotToday_cnt_T_btn.setObjectName("plotToday_cnt_T_btn")
        self.plotAllDays_temp_T_btn = QtWidgets.QPushButton(self.groupBox_8)
        self.plotAllDays_temp_T_btn.setGeometry(QtCore.QRect(330, 110, 131, 31))
        self.plotAllDays_temp_T_btn.setObjectName("plotAllDays_temp_T_btn")
        self.plotToday_temp_T_btn = QtWidgets.QPushButton(self.groupBox_8)
        self.plotToday_temp_T_btn.setGeometry(QtCore.QRect(470, 110, 131, 31))
        self.plotToday_temp_T_btn.setObjectName("plotToday_temp_T_btn")
        self.layoutWidget2 = QtWidgets.QWidget(self.groupBox_8)
        self.layoutWidget2.setGeometry(QtCore.QRect(10, 70, 316, 21))
        self.layoutWidget2.setObjectName("layoutWidget2")
        self.gridLayout_2 = QtWidgets.QGridLayout(self.layoutWidget2)
        self.gridLayout_2.setContentsMargins(0, 0, 0, 0)
        self.gridLayout_2.setObjectName("gridLayout_2")
        self.ON_Count_T = QtWidgets.QLabel(self.layoutWidget2)
        self.ON_Count_T.setObjectName("ON_Count_T")
        self.gridLayout_2.addWidget(self.ON_Count_T, 0, 0, 1, 1)
        self.onCounter_T = QtWidgets.QLabel(self.layoutWidget2)
        self.onCounter_T.setObjectName("onCounter_T")
        self.gridLayout_2.addWidget(self.onCounter_T, 0, 1, 1, 1)
        self.OFF_Count_T = QtWidgets.QLabel(self.layoutWidget2)
        self.OFF_Count_T.setObjectName("OFF_Count_T")
        self.gridLayout_2.addWidget(self.OFF_Count_T, 0, 2, 1, 1)
        self.offCounter_T = QtWidgets.QLabel(self.layoutWidget2)
        self.offCounter_T.setObjectName("offCounter_T")
        self.gridLayout_2.addWidget(self.offCounter_T, 0, 3, 1, 1)
        self.layoutWidget3 = QtWidgets.QWidget(self.groupBox_8)
        self.layoutWidget3.setGeometry(QtCore.QRect(10, 120, 261, 21))
        self.layoutWidget3.setObjectName("layoutWidget3")
        self.gridLayout_3 = QtWidgets.QGridLayout(self.layoutWidget3)
        self.gridLayout_3.setContentsMargins(0, 0, 0, 0)
        self.gridLayout_3.setObjectName("gridLayout_3")
        self.Time_ON_T = QtWidgets.QLabel(self.layoutWidget3)
        self.Time_ON_T.setObjectName("Time_ON_T")
        self.gridLayout_3.addWidget(self.Time_ON_T, 0, 0, 1, 1)
        self.timeOn_T = QtWidgets.QLabel(self.layoutWidget3)
        self.timeOn_T.setObjectName("timeOn_T")
        self.gridLayout_3.addWidget(self.timeOn_T, 0, 1, 1, 1)
        self.Time_OFF_T = QtWidgets.QLabel(self.layoutWidget3)
        self.Time_OFF_T.setObjectName("Time_OFF_T")
        self.gridLayout_3.addWidget(self.Time_OFF_T, 0, 2, 1, 1)
        self.timeOFF_T = QtWidgets.QLabel(self.layoutWidget3)
        self.timeOFF_T.setObjectName("timeOFF_T")
        self.gridLayout_3.addWidget(self.timeOFF_T, 0, 3, 1, 1)
        self.groupBox_9 = QtWidgets.QGroupBox(self.statistics_tab)
        self.groupBox_9.setGeometry(QtCore.QRect(0, 200, 631, 191))
        self.groupBox_9.setObjectName("groupBox_9")
        self.reset_statistics_H_btn = QtWidgets.QPushButton(self.groupBox_9)
        self.reset_statistics_H_btn.setGeometry(QtCore.QRect(540, 20, 91, 31))
        self.reset_statistics_H_btn.setObjectName("reset_statistics_H_btn")
        self.layoutWidget_8 = QtWidgets.QWidget(self.groupBox_9)
        self.layoutWidget_8.setGeometry(QtCore.QRect(10, 30, 446, 21))
        self.layoutWidget_8.setObjectName("layoutWidget_8")
        self.gridLayout_9 = QtWidgets.QGridLayout(self.layoutWidget_8)
        self.gridLayout_9.setContentsMargins(0, 0, 0, 0)
        self.gridLayout_9.setObjectName("gridLayout_9")
        self.Min_H = QtWidgets.QLabel(self.layoutWidget_8)
        self.Min_H.setObjectName("Min_H")
        self.gridLayout_9.addWidget(self.Min_H, 0, 0, 1, 1, QtCore.Qt.AlignRight)
        self.minHum_H = QtWidgets.QLabel(self.layoutWidget_8)
        self.minHum_H.setObjectName("minHum_H")
        self.gridLayout_9.addWidget(self.minHum_H, 0, 1, 1, 1)
        self.Mean_H = QtWidgets.QLabel(self.layoutWidget_8)
        self.Mean_H.setObjectName("Mean_H")
        self.gridLayout_9.addWidget(self.Mean_H, 0, 2, 1, 1, QtCore.Qt.AlignRight)
        self.meanHum_H = QtWidgets.QLabel(self.layoutWidget_8)
        self.meanHum_H.setObjectName("meanHum_H")
        self.gridLayout_9.addWidget(self.meanHum_H, 0, 3, 1, 1)
        self.Max_H = QtWidgets.QLabel(self.layoutWidget_8)
        self.Max_H.setObjectName("Max_H")
        self.gridLayout_9.addWidget(self.Max_H, 0, 4, 1, 1, QtCore.Qt.AlignRight)
        self.maxHum_H = QtWidgets.QLabel(self.layoutWidget_8)
        self.maxHum_H.setObjectName("maxHum_H")
        self.gridLayout_9.addWidget(self.maxHum_H, 0, 5, 1, 1)
        self.plotAllDays_cnt_H_btn = QtWidgets.QPushButton(self.groupBox_9)
        self.plotAllDays_cnt_H_btn.setGeometry(QtCore.QRect(340, 60, 121, 31))
        self.plotAllDays_cnt_H_btn.setObjectName("plotAllDays_cnt_H_btn")
        self.plotToday_cnt_H_btn = QtWidgets.QPushButton(self.groupBox_9)
        self.plotToday_cnt_H_btn.setGeometry(QtCore.QRect(470, 60, 121, 31))
        self.plotToday_cnt_H_btn.setObjectName("plotToday_cnt_H_btn")
        self.plotAllDays_humidity_H_btn = QtWidgets.QPushButton(self.groupBox_9)
        self.plotAllDays_humidity_H_btn.setGeometry(QtCore.QRect(330, 110, 131, 31))
        self.plotAllDays_humidity_H_btn.setObjectName("plotAllDays_humidity_H_btn")
        self.plotToday_humidity_H_btn = QtWidgets.QPushButton(self.groupBox_9)
        self.plotToday_humidity_H_btn.setGeometry(QtCore.QRect(470, 110, 131, 31))
        self.plotToday_humidity_H_btn.setObjectName("plotToday_humidity_H_btn")
        self.layoutWidget_9 = QtWidgets.QWidget(self.groupBox_9)
        self.layoutWidget_9.setGeometry(QtCore.QRect(10, 70, 316, 21))
        self.layoutWidget_9.setObjectName("layoutWidget_9")
        self.gridLayout_10 = QtWidgets.QGridLayout(self.layoutWidget_9)
        self.gridLayout_10.setContentsMargins(0, 0, 0, 0)
        self.gridLayout_10.setObjectName("gridLayout_10")
        self.ON_Count_H = QtWidgets.QLabel(self.layoutWidget_9)
        self.ON_Count_H.setObjectName("ON_Count_H")
        self.gridLayout_10.addWidget(self.ON_Count_H, 0, 0, 1, 1)
        self.onCounter_H = QtWidgets.QLabel(self.layoutWidget_9)
        self.onCounter_H.setObjectName("onCounter_H")
        self.gridLayout_10.addWidget(self.onCounter_H, 0, 1, 1, 1)
        self.offCounter_H = QtWidgets.QLabel(self.layoutWidget_9)
        self.offCounter_H.setObjectName("offCounter_H")
        self.gridLayout_10.addWidget(self.offCounter_H, 0, 3, 1, 1)
        self.OFF_Count_H = QtWidgets.QLabel(self.layoutWidget_9)
        self.OFF_Count_H.setObjectName("OFF_Count_H")
        self.gridLayout_10.addWidget(self.OFF_Count_H, 0, 2, 1, 1)
        self.layoutWidget_10 = QtWidgets.QWidget(self.groupBox_9)
        self.layoutWidget_10.setGeometry(QtCore.QRect(10, 120, 281, 41))
        self.layoutWidget_10.setObjectName("layoutWidget_10")
        self.gridLayout_11 = QtWidgets.QGridLayout(self.layoutWidget_10)
        self.gridLayout_11.setContentsMargins(0, 0, 0, 0)
        self.gridLayout_11.setObjectName("gridLayout_11")
        self.Time_ON_H = QtWidgets.QLabel(self.layoutWidget_10)
        self.Time_ON_H.setObjectName("Time_ON_H")
        self.gridLayout_11.addWidget(self.Time_ON_H, 0, 0, 1, 1)
        self.Time_OFF_H = QtWidgets.QLabel(self.layoutWidget_10)
        self.Time_OFF_H.setObjectName("Time_OFF_H")
        self.gridLayout_11.addWidget(self.Time_OFF_H, 0, 2, 1, 1)
        self.timeOn_H = QtWidgets.QLabel(self.layoutWidget_10)
        self.timeOn_H.setObjectName("timeOn_H")
        self.gridLayout_11.addWidget(self.timeOn_H, 0, 1, 1, 1)
        self.timeOFF_H = QtWidgets.QLabel(self.layoutWidget_10)
        self.timeOFF_H.setObjectName("timeOFF_H")
        self.gridLayout_11.addWidget(self.timeOFF_H, 0, 3, 1, 1)
        self.tabWidget.addTab(self.statistics_tab, "")
        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 640, 24))
        self.menubar.setObjectName("menubar")
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QtWidgets.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)

        self.retranslateUi(MainWindow)
        self.tabWidget.setCurrentIndex(0)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "MainWindow"))
        self.groupBox_3.setTitle(_translate("MainWindow", "Temperatures"))
        self.T3_T.setText(_translate("MainWindow", "T3"))
        self.T1_T.setText(_translate("MainWindow", "T1"))
        self.T4_T.setText(_translate("MainWindow", "T4"))
        self.temperature4_T.setText(_translate("MainWindow", "temperature4"))
        self.temperature3_T.setText(_translate("MainWindow", "temperature3"))
        self.temperature1_T.setText(_translate("MainWindow", "temperature1"))
        self.temperature2_T.setText(_translate("MainWindow", "temperature2"))
        self.T2_T.setText(_translate("MainWindow", "T2"))
        self.groupBox_4.setTitle(_translate("MainWindow", "Humidity"))
        self.H1_H.setText(_translate("MainWindow", "H1"))
        self.humidity1_H.setText(_translate("MainWindow", "humidity1"))
        self.groupBox_5.setTitle(_translate("MainWindow", "Temperature Hysteresis control"))
        self.maxValue_lineEdit.setText(_translate("MainWindow", "max Value"))
        self.minValue_lineEdit.setText(_translate("MainWindow", "min Value"))
        self.Heater.setText(_translate("MainWindow", "Heater: "))
        self.heaterStatus.setText(_translate("MainWindow", "heaterStatus"))
        self.groupBox_6.setTitle(_translate("MainWindow", "Motor Control"))
        self.move_CW_motor_btn.setText(_translate("MainWindow", "Move CW"))
        self.move_CCW_motor_btn.setText(_translate("MainWindow", "Move CCW"))
        self.forceEggsTurn_motor_btn.setText(_translate("MainWindow", "Force Eggs Turn"))
        self.reset_motor_btn.setText(_translate("MainWindow", "Reset"))
        self.layHorizontal_motor_btn.setText(_translate("MainWindow", "Lay Horizontal"))
        self.label.setText(_translate("MainWindow", "Speed [rpm]"))
        self.Motor_Status.setText(_translate("MainWindow", "Motor Status:"))
        self.motorStatus.setText(_translate("MainWindow", "motorStatus"))
        self.groupBox_7.setTitle(_translate("MainWindow", "Overwrite Commands"))
        self.heaterOFF_radioBtn.setText(_translate("MainWindow", "heater OFF"))
        self.heaterAUTO_radioBtn.setText(_translate("MainWindow", "heater AUTO"))
        self.heaterON_radioBtn.setText(_translate("MainWindow", "heater ON"))
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.mainView_tab), _translate("MainWindow", "Main View"))
        self.groupBox_8.setTitle(_translate("MainWindow", "Temperatures Section"))
        self.reset_statistics_T_btn.setText(_translate("MainWindow", "Reset "))
        self.Min_T.setText(_translate("MainWindow", "Min T:"))
        self.minTemp_T.setText(_translate("MainWindow", "minTemp"))
        self.Mean_T.setText(_translate("MainWindow", "Mean T:"))
        self.meanTemp_T.setText(_translate("MainWindow", "meanTemp"))
        self.Max_T.setText(_translate("MainWindow", "Max T:"))
        self.maxTemp_T.setText(_translate("MainWindow", "maxTemp"))
        self.plotAllDays_cnt_T_btn.setText(_translate("MainWindow", "Plot All Days CNT"))
        self.plotToday_cnt_T_btn.setText(_translate("MainWindow", "Plot Today CNT"))
        self.plotAllDays_temp_T_btn.setText(_translate("MainWindow", "Plot All Days T[°C]"))
        self.plotToday_temp_T_btn.setText(_translate("MainWindow", "Plot Today T[°C]"))
        self.ON_Count_T.setText(_translate("MainWindow", "ON Count:"))
        self.onCounter_T.setText(_translate("MainWindow", "onCounter"))
        self.OFF_Count_T.setText(_translate("MainWindow", "OFF Count:"))
        self.offCounter_T.setText(_translate("MainWindow", "offCounter"))
        self.Time_ON_T.setText(_translate("MainWindow", "Time ON:"))
        self.timeOn_T.setText(_translate("MainWindow", "timeOn"))
        self.Time_OFF_T.setText(_translate("MainWindow", "Time OFF:"))
        self.timeOFF_T.setText(_translate("MainWindow", "timeOFF"))
        self.groupBox_9.setTitle(_translate("MainWindow", "Humidity Section"))
        self.reset_statistics_H_btn.setText(_translate("MainWindow", "Reset "))
        self.Min_H.setText(_translate("MainWindow", "Min H:"))
        self.minHum_H.setText(_translate("MainWindow", "minHum"))
        self.Mean_H.setText(_translate("MainWindow", "Mean H:"))
        self.meanHum_H.setText(_translate("MainWindow", "meanHum"))
        self.Max_H.setText(_translate("MainWindow", "Max H:"))
        self.maxHum_H.setText(_translate("MainWindow", "maxHum"))
        self.plotAllDays_cnt_H_btn.setText(_translate("MainWindow", "Plot All Days CNT"))
        self.plotToday_cnt_H_btn.setText(_translate("MainWindow", "Plot Today CNT"))
        self.plotAllDays_humidity_H_btn.setText(_translate("MainWindow", "Plot All Days H[%]"))
        self.plotToday_humidity_H_btn.setText(_translate("MainWindow", "Plot Today H[%]"))
        self.ON_Count_H.setText(_translate("MainWindow", "ON Count:"))
        self.onCounter_H.setText(_translate("MainWindow", "onCounter"))
        self.offCounter_H.setText(_translate("MainWindow", "offCounter"))
        self.OFF_Count_H.setText(_translate("MainWindow", "OFF Count:"))
        self.Time_ON_H.setText(_translate("MainWindow", "Time ON:"))
        self.Time_OFF_H.setText(_translate("MainWindow", "Time OFF:"))
        self.timeOn_H.setText(_translate("MainWindow", "timeOn"))
        self.timeOFF_H.setText(_translate("MainWindow", "timeOFF"))
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.statistics_tab), _translate("MainWindow", "Statistics"))


if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    MainWindow = QtWidgets.QMainWindow()
    ui = Ui_MainWindow()
    ui.setupUi(MainWindow)
    MainWindow.show()
    sys.exit(app.exec_())
