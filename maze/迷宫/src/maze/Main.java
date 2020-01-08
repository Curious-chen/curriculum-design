package maze;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;
import java.util.Stack;

import javafx.animation.Animation.Status;
import javafx.animation.KeyFrame;
import javafx.animation.Timeline;
import javafx.application.Application;

import javafx.collections.ObservableList;
import javafx.event.EventHandler;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.input.KeyCode;
import javafx.scene.input.KeyEvent;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Pane;
import javafx.scene.layout.StackPane;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;
import javafx.scene.shape.Line;
import javafx.scene.shape.Polyline;
import javafx.scene.shape.Rectangle;
import javafx.scene.text.Font;
import javafx.scene.text.FontPosture;
import javafx.scene.text.FontWeight;
import javafx.scene.text.Text;
import javafx.stage.FileChooser;
import javafx.stage.Stage;
import javafx.stage.StageStyle;
import javafx.util.Duration;

public class Main extends Application {
	ArrayList<MPoint> list;// �Թ�
	ArrayList<MPoint> startlist;// �Թ������б�
	ArrayList<MPoint> wayShort;// ���·��
	String[] startPlace;
	String[] endPlace;
	Timeline timeline;// �Թ����ɶ���
	Timeline timeball;// С���ƶ�����
	Polyline ballWay;// С���ƶ�·��
	MazeMo maze;// �Թ�
	Button select;// ���ɰ�ť
	TextField text;// λ����Ϣ��ʾ
	Circle startBall = new Circle();// ��ʼС��
	int len;// �Թ���С����ģ��
	int flog = 0;// ��־����������
	double staX=0,staY=0;
	double enX=0,enY=0;
	public static void main(String[] args) {
		launch(args);

	}

	/*
	 * 
	 * �������棬���ֶ��Թ����Զ��Թ�֮��
	 * 
	 * һ��������ť���ֶ����Զ����˳���ť
	 * 
	 **/
	@Override
	public void start(Stage primaryStage) throws Exception {

		Button buttonMan = new Button("    Manual   maze  ");
		Button buttonAut = new Button("  Automatic maze  ");
		Button buttonQuit = new Button("  Quit  the   maze  ");
		VBox vBox = new VBox();
		vBox.getChildren().addAll(buttonMan, buttonAut, buttonQuit);
		VBox.setMargin(buttonMan, new Insets(20, 20, 20, 20));
		VBox.setMargin(buttonAut, new Insets(20, 20, 20, 20));
		VBox.setMargin(buttonQuit, new Insets(20, 20, 20, 20));
		Scene scene = new Scene(vBox);
		primaryStage.setScene(scene);
		primaryStage.initStyle(StageStyle.TRANSPARENT);//�޴���

		// ���ֶ���manual�����ɽ���
		buttonMan.setOnAction(e -> {
			primaryStage.close();
			Stage stage = new Stage();
			BorderPane pane = (BorderPane) getPane(1, stage, primaryStage);// 1Ϊѡ�����,��ʾѡ���ͼ���ɷ�ʽΪ�ֶ�����
			Scene sceneM = new Scene(pane);
			stage.setScene(sceneM);
			stage.initStyle(StageStyle.TRANSPARENT);//�޴���
			stage.show();
	


		});
		// ���Զ����ɽ���
		buttonAut.setOnAction(e -> {
			primaryStage.close();
			Stage stage = new Stage();
			Pane pane = getPane(2, stage, primaryStage);// 2Ϊѡ�����,��ʾѡ���ͼ���ɷ�ʽΪ�Զ�����
			Scene sceneA = new Scene(pane);
			stage.setScene(sceneA);
			stage.initStyle(StageStyle.TRANSPARENT);//�޴���
			stage.show();
	

		
		});

		// �˳�
		buttonQuit.setOnAction(e -> {
			primaryStage.close();
		});
		primaryStage.show();
		

	}

	/*
	 * ��ҳ�����
	 * 
	 * 
	 * 
	 * 
	 */
	@SuppressWarnings("static-access")
	private Pane getPane(double style, Stage stage, Stage primaryStage) {
		BorderPane borderPane = new BorderPane();// ��ҳ�����
		HBox displayPosition = new HBox(15);

		text = new TextField("��ʾλ����Ϣ���Թ���");
		text.setAlignment(Pos.CENTER);
		text.setEditable(false);
		displayPosition.getChildren().add(text);
		displayPosition.setAlignment(Pos.CENTER);
		borderPane.setTop(displayPosition);

		// ����һ�����Σ�����ȷ���Թ���С
		Rectangle rectangle = new Rectangle(800, 800);
		rectangle.setFill(Color.WHITE);
		rectangle.setStroke(Color.WHEAT);
		Pane pane = new Pane();
		pane.setPrefSize(800, 800);
		

		// ���õ���¼�����ʾλ����Ϣ

		// ͨ��ȷ����pane�е�λ�ã��ҵ��ڵ�Ϊ��
		pane.setOnMouseClicked(o -> {
			if (maze != null) {
				double length = 800 / maze.height;
				String t = "λ��:  ( " + (int) (o.getX() / length) + "   " + (int) (o.getY() / length) + " )";
				text.setText(t);
			}

		});

		// ������壨maze��
		Label fire = new Label("Maze");
		fire.setFont(Font.font("Times new Roman", FontWeight.BOLD, FontPosture.ITALIC, 200));
		pane.getChildren().add(fire);
		fire.setLayoutX(170);
		fire.setLayoutY(170);

		Button buttonSet = new Button(" ��ʼ���� ");
		buttonSet.setDisable(true);
		Button freeMouse = new Button("freedom");
		freeMouse.setDisable(true);
		Button singleWay = new Button("����Ѱ·");
		singleWay.setDisable(true);
		Button buttonStartAndPause = new Button("��ʼ/��ͣѰ·");
		buttonStartAndPause.setDisable(true);
		Button buttonErgodic = new Button("   ����      ");
		buttonErgodic.setDisable(true);
		Button buFinfShortWay = new Button(" ���·��  ");
		buFinfShortWay.setDisable(true);
		Button buttonInitialise = new Button("  ��ʼ��    ");
		buttonInitialise.setDisable(true);
		Button buttonReturn = new Button("    ����      ");

		VBox vBox = new VBox(15);
		vBox.getChildren().addAll(buttonSet, freeMouse, singleWay, buttonStartAndPause, buttonErgodic, buFinfShortWay,
				buttonInitialise, buttonReturn);
		vBox.setPadding(new Insets(15));
		vBox.setSpacing(50);
		borderPane.setRight(vBox);
		borderPane.setCenter(pane);
		borderPane.setPadding(new Insets(15));
		// �����Զ�ѡ��ҳ��
		if (style == 1) {
			select = new Button("�Թ�TxT�ļ�");
			borderPane.setBottom(select);
			borderPane.setMargin(select, new Insets(15));
			borderPane.setAlignment(select, Pos.CENTER);
			select.setOnAction(e -> {// �ֶ������Թ���ť
				buttonSet.setDisable(true);
				buttonInitialise.setDisable(false);
				FileChooser fileChooser = new FileChooser();
				fileChooser.setTitle("ѡ��txt�ļ�");
				fileChooser.setInitialDirectory(new File("H:\\JAVA\\11703990535\\�Թ�\\�Թ���ͼ"));
				File file = fileChooser.showOpenDialog(primaryStage);

				if (file != null && file.getAbsolutePath().startsWith("H:\\JAVA\\11703990535\\�Թ�\\�Թ���ͼ")) {
					Scanner sc = null;
					select.setDisable(true);
					try {
						sc = new Scanner(file);

					} catch (Exception e1) {
						// TODO Auto-generated catch block
						System.out.println("ѡ�����");
					}

					list = new ArrayList<>();

					ArrayList<String> num = new ArrayList<>();
					while (sc.hasNext()) {
						num.add(sc.next());// ÿ��4λ��������һ�����������Ƿ���ǽ

					}
					// ��¼ÿ���������
					int number = (int) Math.sqrt(num.size());
					for (int i = 0; i < num.size(); i++) {
						String digi = num.get(i);
						MPoint point = new MPoint(i % number, i / number);
						if (digi.charAt(0) == '0')
							point.setUp();
						if (digi.charAt(1) == '0')
							point.setRight();
						if (digi.charAt(2) == '0')
							point.setDown();
						if (digi.charAt(3) == '0')
							point.setLeft();
						list.add(point);
					}
					for (int i = 0; i < list.size(); i++)
						list.get(i).visted = true;
					maze = new MazeMo();
					maze.setHeight(number);
					maze.setWidth(number);
					setMazePane(pane, buttonSet);
				}

			});
		}

		// �����Զ�����ҳ��
		if (style == 2) {
			HBox hBox = new HBox(30);
			TextField textField = new TextField("20");
			select = new Button("����");
			hBox.getChildren().addAll(new Label("SIZE"), textField, select);
			hBox.setPadding(new Insets(15));
			borderPane.setBottom(hBox);
			hBox.setAlignment(Pos.CENTER);
			// �Թ��Զ����ɼ�
			select.setOnAction(e -> {// �Զ������Թ���ť
				try {
					buttonSet.setDisable(true);
					setMazePane(buttonSet, textField.getText(), textField.getText(), pane);
					select.setDisable(true);
				} catch (Exception m) {
					Stage error = new Stage();
					Text textError1 = new Text("��ȷ�������Ƿ�Ϊ����");
					Text textError2 = new Text("������˳�");
					textError1.setFont(Font.font("Times new Roman", FontWeight.BOLD, FontPosture.ITALIC, 40));
					textError1.setFill(Color.RED);
					textError2.setFont(Font.font("Times new Roman", FontWeight.BOLD, FontPosture.ITALIC, 20));
					textError2.setFill(Color.AQUA);
					VBox stackPane = new VBox(20);
					stackPane.setAlignment(Pos.CENTER);
					stackPane.getChildren().addAll(textError1, textError2);
					error.setScene(new Scene(stackPane, 500, 500));
					error.show();
					stackPane.setOnKeyPressed(r -> {
						error.close();
					});
					stackPane.requestFocus();
				}
				buttonInitialise.setDisable(false);// ��ʼ����ť��

			});

			// ENTER����
			textField.setOnKeyPressed(e -> {

				if (e.getCode() == KeyCode.ENTER && !select.isDisable()) {
					try {
						buttonSet.setDisable(true);
						setMazePane(buttonSet, textField.getText(), textField.getText(), pane);
						select.setDisable(true);
					} catch (Exception m) {
						Stage error = new Stage();
						Text textError1 = new Text("��ȷ�������Ƿ�Ϊ����");
						Text textError2 = new Text("������˳�");
						textError1.setFont(Font.font("Times new Roman", FontWeight.BOLD, FontPosture.ITALIC, 40));
						textError1.setFill(Color.RED);
						textError2.setFont(Font.font("Times new Roman", FontWeight.BOLD, FontPosture.ITALIC, 20));
						textError2.setFill(Color.AQUA);
						VBox stackPane = new VBox(20);
						stackPane.setAlignment(Pos.CENTER);
						stackPane.getChildren().addAll(textError1, textError2);
						error.setScene(new Scene(stackPane, 500, 500));
						error.show();
						stackPane.setOnKeyPressed(r -> {
							error.close();
						});
						stackPane.requestFocus();
					}
					buttonSet.setDisable(false);// ��ʼ������ť��
					buttonInitialise.setDisable(false);// ��ʼ����ť��
				}

			});

		}
		/*
		 * 
		 * �Թ����������ã���ʼ������ť�� �����ٶȣ���ʼλ�ã��յ�λ��
		 * 
		 * 
		 */
		buttonSet.setOnAction(e -> {// ��ʼ�������ð�ť
			if (maze != null) {
				int h = maze.getHeight(), w = maze.getWidth();
				VBox vBoxC = new VBox(20);

				HBox hBoxC1 = new HBox(15);
				TextField textFieldc = new TextField(0 + "  " + (h - 1));
				hBoxC1.getChildren().addAll(new Label("��ʼ����"), textFieldc);
				hBoxC1.setPadding(new Insets(15));

				// ��ȡ����
				textFieldc.setOnMouseClicked(value -> {
					if (!text.getText().startsWith("��ʾλ����Ϣ")) {
						textFieldc.setText(
								text.getText().substring(text.getText().indexOf('(') + 1, text.getText().indexOf(')')));
						text.setText("��ʾλ����Ϣ���Թ���");
					}
				});

				HBox hBoxC2 = new HBox(15);
				TextField textFieldc2 = new TextField((w - 1) + "  " + 0);
				hBoxC2.getChildren().addAll(new Label("�յ�����"), textFieldc2);
				hBoxC2.setPadding(new Insets(15));

				// ��ȡ����
				textFieldc2.setOnMouseClicked(value -> {
					if (!text.getText().startsWith("��ʾλ����Ϣ")) {
						textFieldc2.setText(
								text.getText().substring(text.getText().indexOf('(') + 1, text.getText().indexOf(')')));
						text.setText("��ʾλ����Ϣ���Թ���");
					}
				});

				HBox hBoxS = new HBox(15);
				TextField textFieldS = new TextField("5");
				hBoxS.getChildren().addAll(new Label("    �ٶ�   "), textFieldS);
				hBoxS.setPadding(new Insets(15));

				HBox hBoxB = new HBox();
				Button buttonSure = new Button("ȷ��");
				hBoxB.getChildren().add(buttonSure);
				hBoxB.setAlignment(Pos.CENTER_RIGHT);
				hBoxB.setPadding(new Insets(15));

				Text textB = new Text("С����������");

				vBoxC.getChildren().addAll(textB, hBoxC1, hBoxC2, hBoxS, hBoxB);
				Stage stageFind = new Stage();
				stageFind.setScene(new Scene(vBoxC));
				stageFind.show();
				stageFind.setX(1420);
				stageFind.setY(100);

				buttonSure.setOnAction(E -> {// �ٶ�����

					startPlace = textFieldc.getText().split("  ");
					endPlace = textFieldc2.getText().split("  ");
					try {
						int startX = Integer.valueOf(startPlace[0].trim()),
								startY = Integer.valueOf(startPlace[1].trim());// ������������ֻ�
						int endX = Integer.valueOf(endPlace[0].trim()), endY = Integer.valueOf(endPlace[1].trim());// ���յ��������ֻ�
						if ((startX >= w || startX < 0) || (startY >= w || startY < 0) || (endX >= w || endX < 0)
								|| (endY >= w | endY < 0)) {
							throw new Exception("��С����");
						}
						double speed = Double.valueOf(textFieldS.getText().trim());
						startBall = new Circle(pane.getWidth() / w / 2 * 0.7, Color.BLUE);

						goMaze(pane, startX, startY, endX, endY, speed, buttonStartAndPause, singleWay, buttonErgodic,freeMouse);
						stageFind.close();
						startBall.setCenterX(pane.getWidth() / h / 2 + startX * pane.getWidth() / h);
						startBall.setCenterY(pane.getWidth() / h / 2 + startY * pane.getWidth() / h);
						buttonErgodic.setDisable(false);
						buttonStartAndPause.setDisable(false);
						freeMouse.setDisable(false);
					} catch (Exception c) {
						Stage error = new Stage();
						Text textError1 = new Text("��ȷ�������Ƿ���ȷ(Ĭ�����ݵ�ֵΪ�����Сֵ)");
						Text textError2 = new Text("������˳�");
						textError1.setFont(Font.font("Times new Roman", FontWeight.BOLD, FontPosture.ITALIC, 25));
						textError1.setFill(Color.RED);
						textError2.setFont(Font.font("Times new Roman", FontWeight.BOLD, FontPosture.ITALIC, 20));
						textError2.setFill(Color.AQUA);
						VBox stackPane = new VBox(20);
						stackPane.setAlignment(Pos.CENTER);
						stackPane.getChildren().addAll(textError1, textError2);
						error.setScene(new Scene(stackPane, 700, 500));
						error.show();
						stackPane.setOnKeyPressed(r -> {
							error.close();
						});
						stackPane.requestFocus();

					}

				});
				buttonSure.setOnKeyPressed(s -> {
					if (s.getCode() == KeyCode.ENTER) {
						startPlace = textFieldc.getText().split("  ");
						endPlace = textFieldc2.getText().split("  ");
						try {
							int startX = Integer.valueOf(startPlace[0].trim()),
									startY = Integer.valueOf(startPlace[1].trim());// ������������ֻ�
							int endX = Integer.valueOf(endPlace[0].trim()), endY = Integer.valueOf(endPlace[1].trim());// ���յ��������ֻ�
							double speed = Double.valueOf(textFieldS.getText().trim());
							startBall = new Circle(pane.getWidth() / w / 2 * 0.7, Color.BLUE);

							goMaze(pane, startX, startY, endX, endY, speed, buttonStartAndPause, singleWay,
									buttonErgodic,freeMouse);
							stageFind.close();
							startBall.setCenterX(pane.getWidth() / h / 2 + startX * pane.getWidth() / h);
							startBall.setCenterY(pane.getWidth() / h / 2 + startY * pane.getWidth() / h);
							pane.getChildren().add(startBall);
							buttonErgodic.setDisable(false);
							buttonStartAndPause.setDisable(false);
						} catch (Exception c) {
							Stage error = new Stage();
							Text textError = new Text("��ȷ�������Ƿ���ȷ(Ĭ�����ݵ�ֵΪ�����Сֵ)");
							StackPane stackPane = new StackPane();
							stackPane.getChildren().add(textError);
							error.setScene(new Scene(stackPane, 400, 100));
							error.show();
						}
					}
				});
				buttonSure.requestFocus();
			}
			buttonSet.setDisable(true);

		});

		//����һ���������ü����¼�һֱ������С����
		Timeline requestFocus=new Timeline(new KeyFrame(Duration.millis(1), c->{
			//���m�����c������С����
			startBall.requestFocus();
			
			//�Д�С���Ƿ��_�˽K�c
			if(startBall.getCenterX()==enX&&startBall.getCenterY()==enY)
			{
				text.setText("�����յ�");
			}
			
		
		}));
		requestFocus.setCycleCount(Timeline.INDEFINITE);
		

		
		//��ťfreedom,������ǽض϶�����Ӧ
		freeMouse.setOnAction(e->{
			startBall.setFill(new Color(Math.random(),Math.random(),Math.random(),Math.random()*0.4+0.6));
			int endX = Integer.valueOf(endPlace[0].trim()), endY = Integer.valueOf(endPlace[1].trim());// ���յ��������ֻ�
			enX=pane.getWidth() / maze.getHeight() / 2 + endX * pane.getWidth() / maze.getHeight();
			enY=pane.getWidth() / maze.getHeight() / 2 + endY * pane.getWidth() / maze.getHeight();
			if(requestFocus.getStatus()!=Status.RUNNING) {
				//�ƶ��¼�
				staX=startBall.getCenterX();staY=startBall.getCenterY();
				EventHandler<KeyEvent> move=new EventHandler<KeyEvent>() {
					int startX = Integer.valueOf(startPlace[0].trim()),
					startY = Integer.valueOf(startPlace[1].trim());// ������������ֻ�
					int len=maze.getHeight();
					MPoint currentPosition=list.get(startX+startY*len);
					double leth = 800 / len;// ��õ�λ����
					
					@Override
					public void handle(KeyEvent event) {
						int x,y;
						switch(event.getCode()) {
						case DOWN:
							 x = currentPosition.getX(); y = currentPosition.getY();
							if (currentPosition.getDown() == 0) {
								startBall.setCenterY(startBall.getCenterY() + leth);
								currentPosition = list.get(x + (y + 1) * len);
							}break;
						case UP:
						 x = currentPosition.getX(); y = currentPosition.getY();
						if (currentPosition.getUp() == 0) {
							startBall.setCenterY(startBall.getCenterY() - leth);
							currentPosition = list.get(x + (y - 1) * len);
						}break;
						case RIGHT:
							 x = currentPosition.getX(); y = currentPosition.getY();
							if (currentPosition.getRight() == 0) {
								startBall.setCenterX(startBall.getCenterX() + leth);
								currentPosition = list.get(x + 1 + y * len);
							}break;
						case LEFT:
							 x = currentPosition.getX(); y = currentPosition.getY();
							if (currentPosition.getLeft() == 0) {
								startBall.setCenterX(startBall.getCenterX() - leth);
								currentPosition = list.get(x - 1 + y * len);
							}break;
						default:
							break;
						
						}
						
					}
				};
				buttonStartAndPause.setDisable(true);
				buttonErgodic.setDisable(true);
				singleWay.setDisable(true);
				requestFocus.play();
				//���Ƅ��¼���ӵ�startBall��
				startBall.setOnKeyPressed(move);
				}
			else {
				requestFocus.pause();
				buttonErgodic.setDisable(false);
				singleWay.setDisable(false);
				buttonStartAndPause.setDisable(false);
				startBall.setCenterX(staX);
				startBall.setCenterY(staY);
				buttonInitialise.requestFocus();
			
				}
		});
		
		
		// ����������㷨��

		buttonErgodic.setOnAction(e -> {// ������ť
			if (startPlace != null) {
				freeMouse.setDisable(true);
				buFinfShortWay.setDisable(false);
				len = maze.getHeight();
				int startX = Integer.valueOf(startPlace[0].trim()), startY = Integer.valueOf(startPlace[1].trim());
				Queue<MPoint> queue = new LinkedList<>();
				MPoint startPoint = list.get(startX + startY * len);
				startPoint.setPre(null);
				queue.offer(startPoint);

				while (!queue.isEmpty()) {
					boolean Go = false;
					MPoint p = queue.remove();
					p.visted = false;
					int x = p.getX(), y = p.getY();
					if (p.getRight() == 0 && list.get(x + 1 + y * len).visted) {
						Go = true;
						queue.offer(list.get(x + 1 + y * len));
						list.get(x + 1 + y * len).setPre(p);
					}
					if (p.getDown() == 0 && list.get(x + (y + 1) * len).visted) {
						Go = true;
						queue.offer(list.get(x + (y + 1) * len));
						list.get(x + (y + 1) * len).setPre(p);
					}
					if (p.getLeft() == 0 && list.get(x - 1 + y * len).visted) {
						Go = true;
						queue.offer(list.get(x - 1 + y * len));
						list.get(x - 1 + y * len).setPre(p);
					}
					if (p.getUp() == 0 && list.get(x + (y - 1) * len).visted) {
						Go = true;
						queue.offer(list.get(x + (y - 1) * len));
						list.get(x + (y - 1) * len).setPre(p);
					}
					if (!Go) {
						Polyline way = new Polyline();
						way.setStroke(Color.GREEN);
						ObservableList<Double> wayPoint = way.getPoints();
						while (p.getPre() != null) {
							double Lx = pane.getWidth() / len * (p.getX() + 0.58),
									Ly = pane.getHeight() / len * (p.getY() + 0.58);
							wayPoint.addAll(Lx, Ly);
							p = p.getPre();
						}
						wayPoint.addAll(pane.getWidth() / len * (p.getX() + 0.58),
								pane.getHeight() / len * (p.getY() + 0.58));
						pane.getChildren().add(way);
					}

				} // list��Ϊtrue
				for (int i = 0; i < list.size(); i++)
					list.get(i).visted = true;
			}
		});

		// ���·��
		buFinfShortWay.setOnAction(e -> {// ���·����ť
		//	RsetPane(pane);
			singleWay.setDisable(true);
			buttonErgodic.setDisable(true);
			buFinfShortWay.setDisable(true);
			buttonStartAndPause.setDisable(true);
			int endX = Integer.valueOf(endPlace[0].trim()), endY = Integer.valueOf(endPlace[1].trim());
			Polyline shortway = new Polyline();
			shortway.setStroke(Color.RED);
			shortway.setStrokeWidth((double) 800 / len * 0.4);
			ObservableList<Double> wayPoint = shortway.getPoints();
			MPoint p = list.get(endX + endY * len);
			while (p.getPre() != null) {
				double x = pane.getWidth() / len * (p.getX() + 0.6), y = pane.getHeight() / len * (p.getY() + 0.6);
				wayPoint.addAll(x, y);
				p = p.getPre();
			}
//			ballWay.setStroke(Color.BLUE);
//			ballWay.setStrokeWidth(800 / len * 0.2);

			pane.getChildren().addAll(shortway, ballWay);
		});

		// ��ʼ��
		buttonInitialise.setOnAction(e -> {
			if (timeball != null)
				timeball.pause();
			RsetPane(pane);
			startPlace = null;
			endPlace = null;
			buttonSet.setDisable(false);
			buttonErgodic.setDisable(true);
			buFinfShortWay.setDisable(true);
			buttonStartAndPause.setDisable(true);
			singleWay.setDisable(true);
		});

		// ���ؼ�
		buttonReturn.setOnAction(e -> {
			stage.close();
			primaryStage.show();
			maze = null;
			list = null;

		});

		// pane.getChildren().add(new Rectangle(100,100,500,500));
		return borderPane;
	}

	// ���Թ����滭��
	private void setMazePane(Pane pane, Button buttonSet) {
		Rectangle rectangle = new Rectangle(800, 800);
		rectangle.setFill(Color.WHITE);
		rectangle.setStroke(Color.BLACK);
		pane.getChildren().add(rectangle);
		int w = maze.getWidth(), h = maze.getHeight();
		double dwlengh = pane.getWidth() / w, dhlenth = pane.getHeight() / h;
		@SuppressWarnings("unchecked")
		ArrayList<MPoint> points = (ArrayList<MPoint>) list.clone();
		timeline = new Timeline(new KeyFrame(Duration.millis(10), ed -> {
			MPoint point = points.remove(0);
			int x = point.getX(), y = point.getY();

			Line line;
			if (point.getUp() == 1) {
				line = new Line();
				line.setStartX(x * dwlengh);
				line.setStartY(y * dhlenth);
				line.setEndX((x + 1) * dwlengh);
				line.setEndY(y * dhlenth);
				pane.getChildren().add(line);

			}
			if (point.getDown() == 1) {
				line = new Line();
				line.setStartX(x * dwlengh);
				line.setStartY((y + 1) * dhlenth);
				line.setEndX((x + 1) * dwlengh);
				line.setEndY((y + 1) * dhlenth);
				pane.getChildren().add(line);

			}
			if (point.getRight() == 1) {
				line = new Line();
				line.setStartX((x + 1) * dwlengh);
				line.setStartY(y * dhlenth);
				line.setEndX((x + 1) * dwlengh);
				line.setEndY((y + 1) * dhlenth);
				pane.getChildren().add(line);
			}
			if (point.getLeft() == 1) {
				line = new Line();
				line.setStartX(x * dwlengh);
				line.setStartY(y * dhlenth);
				line.setEndX(x * dwlengh);
				line.setEndY((y + 1) * dhlenth);
				pane.getChildren().add(line);
				// line.setStroke(new Color(0, 0,0, 0));
			}

			if (points.isEmpty()) {
				timeline.pause();
				select.setDisable(false);
				buttonSet.setDisable(false);
			}

		}));

		timeline.setCycleCount(Timeline.INDEFINITE);
		timeline.play();
	}

	private void setMazePane(Button buttonSet, String text, String text2, Pane pane) {
		maze = new MazeMo(Integer.valueOf(text), Integer.valueOf(text2));
		Rectangle rectangle = new Rectangle(800, 800);
		rectangle.setFill(Color.WHITE);
		rectangle.setStroke(Color.BLACK);
		pane.getChildren().add(rectangle);
		list = maze.getMaze();
		int w = maze.getWidth(), h = maze.getHeight();
		double dwlengh = pane.getWidth() / w, dhlenth = pane.getHeight() / h;

		Polyline lines = new Polyline();
		ObservableList<Double> way = lines.getPoints();
		lines.setStroke(Color.GRAY);
		lines.setStrokeWidth(dhlenth);
		pane.getChildren().add(lines);

		@SuppressWarnings("unchecked")
		ArrayList<MPoint> points = (ArrayList<MPoint>) startlist.clone();

		// �����Թ�����·�������Թ�ͼ
		timeline = new Timeline(new KeyFrame(Duration.millis(10), ed -> {
			MPoint point = points.remove(0);
			int x = point.getX(), y = point.getY();

			way.addAll((dwlengh / 2 + x * dwlengh), (dhlenth / 2 + y * dhlenth));
			// ÿ������Ϊһ�����꣺·������ʱ�������
			if (way.size() >= 6 && (way.get(way.size() - 2).equals(way.get(way.size() - 6)))
					&& ((way.get(way.size() - 1).equals(way.get(way.size() - 5))))) {
				way.remove(way.size() - 1);
				way.remove(way.size() - 1);
				way.remove(way.size() - 1);
				way.remove(way.size() - 1);

			}
			// ���Թ�
			Line line;
			if (point.getUp() == 1) {
				line = new Line();
				line.setStartX(x * dwlengh);
				line.setStartY(y * dhlenth);
				line.setEndX((x + 1) * dwlengh);
				line.setEndY(y * dhlenth);
				pane.getChildren().add(line);

			}
			if (point.getDown() == 1) {
				line = new Line();
				line.setStartX(x * dwlengh);
				line.setStartY((y + 1) * dhlenth);
				line.setEndX((x + 1) * dwlengh);
				line.setEndY((y + 1) * dhlenth);
				pane.getChildren().add(line);

			}
			if (point.getRight() == 1) {
				line = new Line();
				line.setStartX((x + 1) * dwlengh);
				line.setStartY(y * dhlenth);
				line.setEndX((x + 1) * dwlengh);
				line.setEndY((y + 1) * dhlenth);
				pane.getChildren().add(line);
			}
			if (point.getLeft() == 1) {
				line = new Line();
				line.setStartX(x * dwlengh);
				line.setStartY(y * dhlenth);
				line.setEndX(x * dwlengh);
				line.setEndY((y + 1) * dhlenth);
				pane.getChildren().add(line);
				// line.setStroke(new Color(0, 0,0, 0));
			}
			// �Թ����ҵ��յ�
			if (points.isEmpty()) {
				timeline.pause();// �����ر�
				select.setDisable(false);// ѡ���Թ���С���ɰ�ť����
				buttonSet.setDisable(false);// ��ʼ������ť����
			}

		}));

		timeline.setCycleCount(Timeline.INDEFINITE);
		timeline.play();

	}

	/*
	 * Ѱ·���� �������ַ��ƣ�������ȣ�
	 * 
	 * 
	 * 
	 */
	private void goMaze(Pane pane, int startX, int startY, int endX, int endY, double speed, Button buttonStartAndPause,
			Button singleWay, Button Ergodic,Button freeMouse) {
		int top = 0;
		ArrayList<MPoint> goway = new ArrayList<MPoint>();
		int width = maze.getWidth();
		double lenth = pane.getWidth() / width;
		goway.add(list.get(startX + startY * width));// ��������ȡ����ʼλ�ý��
		// ���ַ��� �жϷ���

		// �����Kĩ����
		Rectangle startRec = new Rectangle(startX * lenth, startY * lenth, lenth, lenth);
		Rectangle endRec = new Rectangle(+endX * lenth, endY * lenth, lenth, lenth);
		startRec.setFill(Color.BLUE);
		endRec.setFill(Color.RED);
		pane.getChildren().addAll(endRec, startBall);

		// ���������Ѱ·
		Polyline line = new Polyline();
		ObservableList<Double> way = line.getPoints();
		line.setStroke(new Color(0, 0, 0, 0));// ��¼С���ߵ�����λ��
		while (true) {
			MPoint point = (MPoint) goway.get(top);
			int x = point.getX(), y = point.getY();
			way.addAll((lenth / 2 + x * lenth), (lenth / 2 + y * lenth));
			if (x == endX && y == endY)
				break;
			// �� �ң��ϣ��£����˳����
			Stack<Integer> dirs = new Stack<>();
			if (point.getLeft() == 0 && list.get((x - 1) + y * width).visted)
				dirs.add(0);
			if (point.getDown() == 0 && list.get(x + (y + 1) * width).visted)
				dirs.add(1);
			if (point.getUp() == 0 && list.get(x + (y - 1) * width).visted)
				dirs.add(2);
			if (point.getRight() == 0 && list.get((x + 1) + y * width).visted)
				dirs.add(3);
			if (dirs.size() == 0) {
				goway.remove(top);
				top--;
			} else {

				top++;
				int dir = dirs.peek();
				switch (dir) {
				case 0:
					goway.add(list.get((x - 1) + y * width));
					list.get((x - 1) + y * width).visted = false;
					break;// left
				case 1:
					goway.add(list.get(x + (y + 1) * width));
					list.get(x + (y + 1) * width).visted = false;
					break;// down
				case 2:
					goway.add(list.get(x + (y - 1) * width));
					list.get(x + (y - 1) * width).visted = false;
					break;// up
				case 3:
					goway.add(list.get((x + 1) + y * width));
					list.get((x + 1) + y * width).visted = false;
					break;// right
				}
			}
		}

		// ��¼С������·������̾���
		Polyline line2 = new Polyline();
		ballWay = new Polyline();// line2,ballWay,�������·�����o
		ObservableList<Double> wayPoint = line2.getPoints();
		ObservableList<Double> wayPointball = ballWay.getPoints();
		for (int i = 0; i < goway.size(); i++) {
			double x = goway.get(i).getX(), y = goway.get(i).getY();
			wayPoint.addAll((lenth / 2 * 0.8 + x * lenth), (lenth / 2 * 0.8 + y * lenth));
			wayPointball.addAll((lenth / 2 * 0.8 + x * lenth), (lenth / 2 * 0.8 + y * lenth));
		}

		for (int i = 0; i < list.size(); i++)
			list.get(i).visted = true;

		// �β���·
		/*
		 * ��һ���������ǻ�һС��
		 * 
		 * 
		 */
		singleWay.setDisable(false);
		ArrayList<Circle> tested = new ArrayList<>();
		singleWay.setOnAction(e -> {

			// ���ܱ���
			freeMouse.setDisable(true);
			Ergodic.setDisable(true);
			if (way.size() >= 2) {
				Circle fz = new Circle(startBall.getRadius(), startBall.getFill());
				fz.setCenterX(way.remove(0));
				fz.setCenterY(way.remove(0));
				pane.getChildren().add(fz);
				if (tested.size() >= 2) {
					Circle t1 = tested.get(tested.size() - 1);
					Circle t2 = tested.get(tested.size() - 2);
					if (t2.getCenterX() == fz.getCenterX() && t2.getCenterY() == fz.getCenterY()) {
						t1.setFill(Color.RED);
						t2.setFill(Color.RED);
						tested.remove(tested.size() - 1);
						tested.remove(tested.size() - 1);
					}
				}
				tested.add(fz);
			}
			if (way.isEmpty()) {
				line2.setStroke(Color.BLUE);
				line2.setStrokeWidth(lenth * 0.2);
				buttonStartAndPause.setDisable(true);
				singleWay.setDisable(true);
				Ergodic.setDisable(false);
				try {
					pane.getChildren().add(line2);

				} catch (Exception d) {
					System.out.println("·������ʾ");
				}
			}

		});

		// ����С����ʻ����
		timeball = new Timeline(new KeyFrame(Duration.millis(1000 / speed), ed -> {
			if (way.size() >= 2) {
				Circle fz = new Circle(startBall.getRadius(), startBall.getFill());
				fz.setCenterX(way.remove(0));
				fz.setCenterY(way.remove(0));
				pane.getChildren().add(fz);
				if (tested.size() >= 2) {
					Circle t1 = tested.get(tested.size() - 1);
					Circle t2 = tested.get(tested.size() - 2);
					if (t2.getCenterX() == fz.getCenterX() && t2.getCenterY() == fz.getCenterY()) {
						t1.setFill(Color.RED);
						t2.setFill(Color.RED);
						tested.remove(tested.size() - 1);
						tested.remove(tested.size() - 1);
					}
				}
				tested.add(fz);
			}
			if (way.isEmpty()) {
				line2.setStroke(Color.BLUE);
				line2.setStrokeWidth(lenth * 0.2);
				pane.getChildren().add(line2);
				timeball.pause();
				buttonStartAndPause.setDisable(true);
				singleWay.setDisable(true);
				Ergodic.setDisable(false);

			}

		}));

		timeball.setCycleCount(Timeline.INDEFINITE);
		// ��ʼ����ͣ��ť
		buttonStartAndPause.setOnAction(e -> {
			Ergodic.setDisable(true);
			freeMouse.setDisable(true);
			if (!way.isEmpty()) {
				if (timeball.getStatus() != Status.RUNNING)
					timeball.play();
				else
					timeball.pause();
			}

		});
	}

	/*
	 * ʵ�ֳ�ʼ�����ܡ������ο�������ݸ���
	 * 
	 * 
	 * ���ٸ��wһ��
	 * 
	 */
	private void RsetPane(Pane pane) {
		Rectangle rectangle = new Rectangle(800, 800);
		rectangle.setFill(Color.WHITE);
		rectangle.setStroke(Color.BLACK);
		pane.getChildren().add(rectangle);
		int w = maze.getWidth(), h = maze.getHeight();
		double dwlengh = pane.getWidth() / w, dhlenth = pane.getHeight() / h;
		for (int i = 0; i < list.size(); i++) {
			MPoint point = list.get(i);
			int x = point.getX(), y = point.getY();
			Line line;
			if (point.getUp() == 1) {
				line = new Line();
				line.setStartX(x * dwlengh);
				line.setStartY(y * dhlenth);
				line.setEndX((x + 1) * dwlengh);
				line.setEndY(y * dhlenth);
				pane.getChildren().add(line);

			}
			if (point.getDown() == 1) {
				line = new Line();
				line.setStartX(x * dwlengh);
				line.setStartY((y + 1) * dhlenth);
				line.setEndX((x + 1) * dwlengh);
				line.setEndY((y + 1) * dhlenth);
				pane.getChildren().add(line);

			}
			if (point.getRight() == 1) {
				line = new Line();
				line.setStartX((x + 1) * dwlengh);
				line.setStartY(y * dhlenth);
				line.setEndX((x + 1) * dwlengh);
				line.setEndY((y + 1) * dhlenth);
				pane.getChildren().add(line);
			}
			if (point.getLeft() == 1) {
				line = new Line();
				line.setStartX(x * dwlengh);
				line.setStartY(y * dhlenth);
				line.setEndX(x * dwlengh);
				line.setEndY((y + 1) * dhlenth);
				pane.getChildren().add(line);
				// line.setStroke(new Color(0, 0,0, 0));
			}
			// System.out.println(" UP:"+point.getUp()+" Down:"+point.getDown()+"
			// RIGHT:"+point.getRight()+" LEFT:"+point.getLeft());
		}
	}

	class MazeMo {

		private int width = 0;
		private int height = 0;

		public MazeMo() {
			this.width = 4; // �Թ����
			this.height = 4; // �Թ��߶�
		}

		public int getWidth() {
			return width;
		}

		public void setWidth(int width) {
			this.width = width;
		}

		public int getHeight() {
			return height;
		}

		public void setHeight(int height) {
			this.height = height;
		}

		public MazeMo(int width, int height) {
			super();
			this.width = width;
			this.height = height;
		}

		public ArrayList<MPoint> getMaze() {
			ArrayList<MPoint> maze = new ArrayList<MPoint>();
			for (int h = 0; h < height; h++) {
				for (int w = 0; w < width; w++) {
					MPoint point = new MPoint(w, h);
					maze.add(point);
				}
			}
			return CreateMaze(maze);
		}

		// ������ȴ����Թ�
		private ArrayList<MPoint> CreateMaze(ArrayList<MPoint> maze) {
			int x = 0;
			int y = 0;
			ArrayList<MPoint> sweap = new ArrayList<MPoint>();
			startlist = new ArrayList<MPoint>();
			sweap.add(maze.get(x + y * width));
			while (!sweap.isEmpty()) {
				boolean flag = false;
				MPoint pt = (MPoint) sweap.get(sweap.size() - 1);// ȡ��ĩβԪ��
				startlist.add(pt);
				x = pt.getX();
				y = pt.getY();
				pt.visted = true;
				// ����ĸ��������ֵ��ֵ
				Stack<Integer> dir = new Stack<>();
				dir.add(0);// ���
				dir.add(1);// �ұ�
				dir.add(2); // �ϱ�
				dir.add(3);// �±�
				// �ĸ����򶼲�����,����ѭ��
				while (!dir.isEmpty()) {
					int sel = (int) (Math.random() * dir.size());// ���ѡ����
					switch (dir.get(sel)) {
					case 0: // ���
						if ((x - 1) >= 0 && maze.get(x - 1 + y * width).visted == false) {
							maze.get(x + y * width).setLeft();
							maze.get(x - 1 + y * width).setRight();
							sweap.add(maze.get(x - 1 + y * width));
							flag = true;

						}
						break;
					case 1: // �ұ�
						if ((x + 1) < width && maze.get(x + 1 + y * width).visted == false) {

							maze.get(x + y * width).setRight();// ��Ϊ0��ע��0��ʾΪͨ·
							maze.get(x + 1 + y * width).setLeft();
							sweap.add(maze.get(x + 1 + y * width));
							flag = true;
						}
						break;
					case 2: // �ϱ�
						if ((y - 1) >= 0 && maze.get(x + (y - 1) * width).visted == false) {
							maze.get(x + y * width).setUp();
							maze.get(x + (y - 1) * width).setDown();
							sweap.add(maze.get(x + (y - 1) * width));
							flag = true;
						}
						break;
					case 3: // �±�
						if ((y + 1) < height && maze.get(x + (y + 1) * width).visted == false) {
							maze.get(x + y * width).setDown();
							maze.get(x + (y + 1) * width).setUp();
							sweap.add(maze.get(x + (y + 1) * width));
							flag = true;
						}
						break;
					}
					if (flag)// �ж�ѡ��ķ����Ƿ����
						break;
					dir.remove(sel);// û�����Ƴ���ѡ����
				}
				if (!flag) {// �ĸ����򶼲�����
					sweap.remove(sweap.size() - 1);
					/*
					 * 
					 * 
					 * 
					 * ����ֻ����һ��ͨ���յ��·
					 */
					// ѡ��һ����ͻ��
					if ((int) (Math.random() * 10) == 0)// 1/10�Ŀ��� ͻ��
						switch ((int) (Math.random() * 4)) {
						case 0: // ���
							if ((x - 1) >= 0) {
								maze.get(x + y * width).setLeft();
								maze.get(x - 1 + y * width).setRight();

							}
							break;
						case 1: // �ұ�
							if ((x + 1) < width) {

								maze.get(x + y * width).setRight();// ��Ϊ0��ע��0��ʾΪͨ·
								maze.get(x + 1 + y * width).setLeft();

							}
							break;
						case 2: // �ϱ�
							if ((y - 1) >= 0) {
								maze.get(x + y * width).setUp();
								maze.get(x + (y - 1) * width).setDown();

							}
							break;
						case 3: // �±�
							if ((y + 1) < height) {
								maze.get(x + y * width).setDown();
								maze.get(x + (y + 1) * width).setUp();

							}
							break;
						}

				}

			}
			/*
			 * 
			 * 
			 * 
			 * 
			 * ��¼�Թ�
			 */
			PrintWriter writer = null;
			try {
				writer = new PrintWriter("H:\\JAVA\\11703990535\\�Թ�\\�Թ���ͼ\\" + height + "_" + width + ".txt");
			} catch (FileNotFoundException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			for (int i = 0; i < height; i++) {
				for (int j = 0; j < width; j++) {
					MPoint p = maze.get(j + i * width);
					String digi = "" + p.getUp() + p.getRight() + p.getDown() + p.getLeft();
					writer.print(digi + "  ");
					// //
					// if(p.getUp()==1)
					// System.out.print(0);
					// else
					// System.out.print(1);
					// if(p.getRight()==1)
					// System.out.print(0);
					// else
					// System.out.print(1);
					// if(p.getDown()==1)
					// System.out.print(0);
					// else
					// System.out.print(1);
					// if(p.getLeft()==1)
					// System.out.print(0);
					// else
					// System.out.print(1);
					// System.out.print(" ");

				}
				writer.println();
				// System.out.println();

			}
			writer.close();

			return maze;
		}
	}

}
