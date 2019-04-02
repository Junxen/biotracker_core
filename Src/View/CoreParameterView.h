#ifndef COREPARAMETERVIEW_H
#define COREPARAMETERVIEW_H

#include "Interfaces/IView/IViewWidget.h"
#include "View/Utility/SwitchButton.h"
#include "Model/MediaPlayerStateMachine/MediaPlayerStateMachine.h"
#include "util/Config.h"

namespace Ui {
	class CoreParameterView;
}

/**
*	This class contains the 'Experiment' tab and the 'Visualisation options' tab in the GUI
*	It basically displays the current set parameters
*	The
*/

class CoreParameterView : public IViewWidget
{
	Q_OBJECT

public:
	explicit CoreParameterView(QWidget *parent = 0, IController *controller = 0, IModel *model = 0);
	~CoreParameterView();

	QWidget* getTrackerHook();
	void setPermission(std::pair<ENUMS::COREPERMISSIONS, bool> permission);

	// Triggers re-sending essential signals
	void triggerUpdate();

	void areaDescriptorTypeChanged(QString type);

	private slots:

	/*
		VIEW TAB
	*/
	//Enable view
	void on_checkBoxEnableCoreView_stateChanged(int v);
	//Tracing
	void on_comboBoxTracingStyle_currentIndexChanged(const QString & text);
	void on_spinBoxTracingHistoryLength_valueChanged(int i);
	void on_spinBoxTracingSteps_valueChanged(int i);
	void on_comboBoxTracingTimeDegradation_currentIndexChanged(const QString & text);
	void on_checkBoxTracerFrameNumber_stateChanged(int toggle);

	void on_spinBoxTracerProportions_valueChanged(double d);
	void on_checkBoxTracerOrientationLine_stateChanged(int toggle);

	//Track 
	//void on_pushButtonSelectAll_clicked();
	//void on_pushButtonAddTrack_clicked();

	void on_checkBoxIgnoreZoom_stateChanged(int v);

	//Track color
	void on_pushButtonColorChangeBorder_clicked();
	void on_pushButtonColorChangeBorderSelected_clicked();
	void on_pushButtonColorChangeBrush_clicked();
	void on_pushButtonColorchangeBrushSelected_clicked();

	//Track dimensions
	void on_checkBoxTrackOrientationLine_stateChanged(int v);
	void on_checkBoxShowId_stateChanged(int v);


	void on_pushButtonTrackDimensionSetterAll_clicked();
	void on_pushButtonTrackDimensionSetterSelected_clicked();
	void on_pushButtonDefaultDimensions_clicked();

	//Area descriptor
	void on_lineEditRectWidth_textChanged(QString s);
	void on_lineEditRectHeight_textChanged(QString s);
	void on_checkBoxDisplayTrackingArea_stateChanged(int v);
	void on_checkBoxDisplayRectification_stateChanged(int v);
	void on_checkboxTrackingAreaAsEllipse_stateChanged(int v);

	//Annotations
	void on_pushButtonAnnoColor_clicked();

	//Finalize experiment
	//void on_pushButtonFinalizeExperiment_clicked();

	//Misc
	//void on_checkBoxExpertOptions_stateChanged(int v);
	void toggleExpertOptions(bool toggle);
	void on_checkBoxAntialiasingEntities_toggled(bool toggle);
	void on_checkBoxAntialiasingFull_toggled(bool toggle);

	/*
	EXPERIMENT TAB
	*/

	//label_ExpTrialNo
	//label_ExpSrcCnt
	//label_ExpObjCnt
	//pushButton_startExp
	//pushButton_finalizeExp
	void on_pushButton_startExp_clicked();
	void on_pushButton_finalizeExp_clicked();
	//void on_label_ExpSrcCnt_clicked();
	void on_trialHelpButton_clicked();
	void on_pushButton_saveData_clicked();
	void on_pushButton_resetData_clicked();
	void on_pushButton_addTraj_clicked();
	public slots:
	void rcvPlayerParameters(playerParameters* parameters);


public:
	signals :

			/*
			EXPERIMENT TAB
			*/
			void emitEnableTracking();
			void emitDisableTracking();
			void emitActivateTrackingSwitch();
			void emitDeactivateTrackingSwitch();
			void emitStartPlayback();
			void emitStopPlayback();
			void emitPausePlayback();
			void emitTrialStarted(bool started);
			void emitSaveDataToFile();


			//Enable view
			void emitViewSwitch(bool lever);
			//Select all tracks
			//void emitSelectAll();
			//Add tracks
			void emitAddTrack();
			//Ignore zoom
			void emitIgnoreZoom(bool toggle);
			//Track color
			void emitColorChangeBorderAll();
			void emitColorChangeBorderSelected();
			void emitColorChangeBrushAll();
			void emitColorChangeBrushSelected();
			//Track dimensions
			void emitTrackOrientationLine(bool toggle);
			void emitTrackShowId(bool toggle);
			void emitTrackDimensionsAll(int width, int height);
			void emitTrackDimensionsSelected(int width, int height);
			void emitTrackDimensionsSetDefault();
			//Tracing
			void emitTracingHistoryLength(int history);
			void emitTracingStyle(QString style);
			void emitTracingSteps(int steps);
			void emitTracingTimeDegradation(QString degradation);
			void emitTracerFrameNumber(bool toggle);
			//Tracing dimensions
			void emitTracerProportions(float proportion);
			void emitTracerOrientationLine(bool toggle);

			//Area descriptor
			void emitRectDimensions(double w, double h);
			void emitDisplayTrackingArea(bool b);
			void emitDisplayRectification(bool b);
			void emitTrackingAreaAsEllipse(bool b);

			//Annotations
			void emitSetAnnoColor(QColor color);

			//Finalize Experiment
			void emitFinalizeExperiment();

			//Misc
			void emitToggleAntialiasingEntities(bool toggle);
			void emitToggleAntialiasingFull(bool toggle);

private:
	Ui::CoreParameterView *ui;			/**< processed ui file  */

	bool m_viewSwitch;					/**< switch to enable/disable visualization options tab  */
	SwitchButton* _expertSwitch;		/**< switch to expand visualization options tab  */
	bool _trialActive = false;			/**< currently trial active?  */
	bool _trialStarted = false;			/**< was trial started?  */
	QString _currentFile = "No Media";	/**< show media name in experiment tab  */

	Config *_cfg;
	
	// IViewWidget interface
	public slots:

	void getNotified();

	/// fills the ui elements with the current default parameters
	void fillUI();

	/// styles the "visualisation options" tab
	void setStyle();
	void resetTrial();
};

#endif // COREPARAMETERVIEW_H
