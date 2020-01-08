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
	ArrayList<MPoint> list;// 迷宫
	ArrayList<MPoint> startlist;// 迷宫生成列表
	ArrayList<MPoint> wayShort;// 最短路径
	String[] startPlace;
	String[] endPlace;
	Timeline timeline;// 迷宫生成动画
	Timeline timeball;// 小球移动动画
	Polyline ballWay;// 小球移动路径
	MazeMo maze;// 迷宫
	Button select;// 生成按钮
	TextField text;// 位置信息显示
	Circle startBall = new Circle();// 起始小球
	int len;// 迷宫大小（规模）
	int flog = 0;// 标志启动自由行
	double staX=0,staY=0;
	double enX=0,enY=0;
	public static void main(String[] args) {
		launch(args);

	}

	/*
	 * 
	 * 启动界面，有手动迷宫和自动迷宫之分
	 * 
	 * 一共三个按钮，手动，自动，退出按钮
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
		primaryStage.initStyle(StageStyle.TRANSPARENT);//无窗口

		// 打开手动（manual）生成界面
		buttonMan.setOnAction(e -> {
			primaryStage.close();
			Stage stage = new Stage();
			BorderPane pane = (BorderPane) getPane(1, stage, primaryStage);// 1为选择参数,表示选择地图生成方式为手动生成
			Scene sceneM = new Scene(pane);
			stage.setScene(sceneM);
			stage.initStyle(StageStyle.TRANSPARENT);//无窗口
			stage.show();
	


		});
		// 打开自动生成界面
		buttonAut.setOnAction(e -> {
			primaryStage.close();
			Stage stage = new Stage();
			Pane pane = getPane(2, stage, primaryStage);// 2为选择参数,表示选择地图生成方式为自动生成
			Scene sceneA = new Scene(pane);
			stage.setScene(sceneA);
			stage.initStyle(StageStyle.TRANSPARENT);//无窗口
			stage.show();
	

		
		});

		// 退出
		buttonQuit.setOnAction(e -> {
			primaryStage.close();
		});
		primaryStage.show();
		

	}

	/*
	 * 主页面设计
	 * 
	 * 
	 * 
	 * 
	 */
	@SuppressWarnings("static-access")
	private Pane getPane(double style, Stage stage, Stage primaryStage) {
		BorderPane borderPane = new BorderPane();// 主页面设计
		HBox displayPosition = new HBox(15);

		text = new TextField("显示位置信息（迷宫）");
		text.setAlignment(Pos.CENTER);
		text.setEditable(false);
		displayPosition.getChildren().add(text);
		displayPosition.setAlignment(Pos.CENTER);
		borderPane.setTop(displayPosition);

		// 建立一个矩形，用以确定迷宫大小
		Rectangle rectangle = new Rectangle(800, 800);
		rectangle.setFill(Color.WHITE);
		rectangle.setStroke(Color.WHEAT);
		Pane pane = new Pane();
		pane.setPrefSize(800, 800);
		

		// 设置点击事件，显示位置信息

		// 通过确定在pane中的位置，找到节点为置
		pane.setOnMouseClicked(o -> {
			if (maze != null) {
				double length = 800 / maze.height;
				String t = "位置:  ( " + (int) (o.getX() / length) + "   " + (int) (o.getY() / length) + " )";
				text.setText(t);
			}

		});

		// 启动面板（maze）
		Label fire = new Label("Maze");
		fire.setFont(Font.font("Times new Roman", FontWeight.BOLD, FontPosture.ITALIC, 200));
		pane.getChildren().add(fire);
		fire.setLayoutX(170);
		fire.setLayoutY(170);

		Button buttonSet = new Button(" 初始条件 ");
		buttonSet.setDisable(true);
		Button freeMouse = new Button("freedom");
		freeMouse.setDisable(true);
		Button singleWay = new Button("单步寻路");
		singleWay.setDisable(true);
		Button buttonStartAndPause = new Button("开始/暂停寻路");
		buttonStartAndPause.setDisable(true);
		Button buttonErgodic = new Button("   遍历      ");
		buttonErgodic.setDisable(true);
		Button buFinfShortWay = new Button(" 最短路径  ");
		buFinfShortWay.setDisable(true);
		Button buttonInitialise = new Button("  初始化    ");
		buttonInitialise.setDisable(true);
		Button buttonReturn = new Button("    返回      ");

		VBox vBox = new VBox(15);
		vBox.getChildren().addAll(buttonSet, freeMouse, singleWay, buttonStartAndPause, buttonErgodic, buFinfShortWay,
				buttonInitialise, buttonReturn);
		vBox.setPadding(new Insets(15));
		vBox.setSpacing(50);
		borderPane.setRight(vBox);
		borderPane.setCenter(pane);
		borderPane.setPadding(new Insets(15));
		// 进入自动选择页面
		if (style == 1) {
			select = new Button("迷宫TxT文件");
			borderPane.setBottom(select);
			borderPane.setMargin(select, new Insets(15));
			borderPane.setAlignment(select, Pos.CENTER);
			select.setOnAction(e -> {// 手动生成迷宫按钮
				buttonSet.setDisable(true);
				buttonInitialise.setDisable(false);
				FileChooser fileChooser = new FileChooser();
				fileChooser.setTitle("选择txt文件");
				fileChooser.setInitialDirectory(new File("H:\\JAVA\\11703990535\\迷宫\\迷宫地图"));
				File file = fileChooser.showOpenDialog(primaryStage);

				if (file != null && file.getAbsolutePath().startsWith("H:\\JAVA\\11703990535\\迷宫\\迷宫地图")) {
					Scanner sc = null;
					select.setDisable(true);
					try {
						sc = new Scanner(file);

					} catch (Exception e1) {
						// TODO Auto-generated catch block
						System.out.println("选择错误");
					}

					list = new ArrayList<>();

					ArrayList<String> num = new ArrayList<>();
					while (sc.hasNext()) {
						num.add(sc.next());// 每个4位整数代表一个结点的四周是否有墙

					}
					// 记录每个结点的情况
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

		// 进入自动生成页面
		if (style == 2) {
			HBox hBox = new HBox(30);
			TextField textField = new TextField("20");
			select = new Button("生成");
			hBox.getChildren().addAll(new Label("SIZE"), textField, select);
			hBox.setPadding(new Insets(15));
			borderPane.setBottom(hBox);
			hBox.setAlignment(Pos.CENTER);
			// 迷宫自动生成键
			select.setOnAction(e -> {// 自动生成迷宫按钮
				try {
					buttonSet.setDisable(true);
					setMazePane(buttonSet, textField.getText(), textField.getText(), pane);
					select.setDisable(true);
				} catch (Exception m) {
					Stage error = new Stage();
					Text textError1 = new Text("请确定输入是否为整数");
					Text textError2 = new Text("任意键退出");
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
				buttonInitialise.setDisable(false);// 初始化按钮打开

			});

			// ENTER键打开
			textField.setOnKeyPressed(e -> {

				if (e.getCode() == KeyCode.ENTER && !select.isDisable()) {
					try {
						buttonSet.setDisable(true);
						setMazePane(buttonSet, textField.getText(), textField.getText(), pane);
						select.setDisable(true);
					} catch (Exception m) {
						Stage error = new Stage();
						Text textError1 = new Text("请确定输入是否为整数");
						Text textError2 = new Text("任意键退出");
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
					buttonSet.setDisable(false);// 初始条件按钮打开
					buttonInitialise.setDisable(false);// 初始化按钮打开
				}

			});

		}
		/*
		 * 
		 * 迷宫鼠条件设置（初始条件按钮） 包括速度，初始位置，终点位置
		 * 
		 * 
		 */
		buttonSet.setOnAction(e -> {// 初始条件设置按钮
			if (maze != null) {
				int h = maze.getHeight(), w = maze.getWidth();
				VBox vBoxC = new VBox(20);

				HBox hBoxC1 = new HBox(15);
				TextField textFieldc = new TextField(0 + "  " + (h - 1));
				hBoxC1.getChildren().addAll(new Label("起始坐标"), textFieldc);
				hBoxC1.setPadding(new Insets(15));

				// 获取坐标
				textFieldc.setOnMouseClicked(value -> {
					if (!text.getText().startsWith("显示位置信息")) {
						textFieldc.setText(
								text.getText().substring(text.getText().indexOf('(') + 1, text.getText().indexOf(')')));
						text.setText("显示位置信息（迷宫）");
					}
				});

				HBox hBoxC2 = new HBox(15);
				TextField textFieldc2 = new TextField((w - 1) + "  " + 0);
				hBoxC2.getChildren().addAll(new Label("终点坐标"), textFieldc2);
				hBoxC2.setPadding(new Insets(15));

				// 获取坐标
				textFieldc2.setOnMouseClicked(value -> {
					if (!text.getText().startsWith("显示位置信息")) {
						textFieldc2.setText(
								text.getText().substring(text.getText().indexOf('(') + 1, text.getText().indexOf(')')));
						text.setText("显示位置信息（迷宫）");
					}
				});

				HBox hBoxS = new HBox(15);
				TextField textFieldS = new TextField("5");
				hBoxS.getChildren().addAll(new Label("    速度   "), textFieldS);
				hBoxS.setPadding(new Insets(15));

				HBox hBoxB = new HBox();
				Button buttonSure = new Button("确定");
				hBoxB.getChildren().add(buttonSure);
				hBoxB.setAlignment(Pos.CENTER_RIGHT);
				hBoxB.setPadding(new Insets(15));

				Text textB = new Text("小球属性设置");

				vBoxC.getChildren().addAll(textB, hBoxC1, hBoxC2, hBoxS, hBoxB);
				Stage stageFind = new Stage();
				stageFind.setScene(new Scene(vBoxC));
				stageFind.show();
				stageFind.setX(1420);
				stageFind.setY(100);

				buttonSure.setOnAction(E -> {// 速度设置

					startPlace = textFieldc.getText().split("  ");
					endPlace = textFieldc2.getText().split("  ");
					try {
						int startX = Integer.valueOf(startPlace[0].trim()),
								startY = Integer.valueOf(startPlace[1].trim());// 将起点坐标数字化
						int endX = Integer.valueOf(endPlace[0].trim()), endY = Integer.valueOf(endPlace[1].trim());// 将终点坐标数字化
						if ((startX >= w || startX < 0) || (startY >= w || startY < 0) || (endX >= w || endX < 0)
								|| (endY >= w | endY < 0)) {
							throw new Exception("大小错了");
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
						Text textError1 = new Text("请确定输入是否正确(默认数据的值为最大最小值)");
						Text textError2 = new Text("任意键退出");
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
									startY = Integer.valueOf(startPlace[1].trim());// 将起点坐标数字化
							int endX = Integer.valueOf(endPlace[0].trim()), endY = Integer.valueOf(endPlace[1].trim());// 将终点坐标数字化
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
							Text textError = new Text("请确定输入是否正确(默认数据的值为最大最小值)");
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

		//建立一个动画，让键盘事件一直集中在小球上
		Timeline requestFocus=new Timeline(new KeyFrame(Duration.millis(1), c->{
			//持續將焦點集中在小球上
			startBall.requestFocus();
			
			//判斷小球是否到達了終點
			if(startBall.getCenterX()==enX&&startBall.getCenterY()==enY)
			{
				text.setText("到达终点");
			}
			
		
		}));
		requestFocus.setCycleCount(Timeline.INDEFINITE);
		

		
		//按钮freedom,激活或是截断动画响应
		freeMouse.setOnAction(e->{
			startBall.setFill(new Color(Math.random(),Math.random(),Math.random(),Math.random()*0.4+0.6));
			int endX = Integer.valueOf(endPlace[0].trim()), endY = Integer.valueOf(endPlace[1].trim());// 将终点坐标数字化
			enX=pane.getWidth() / maze.getHeight() / 2 + endX * pane.getWidth() / maze.getHeight();
			enY=pane.getWidth() / maze.getHeight() / 2 + endY * pane.getWidth() / maze.getHeight();
			if(requestFocus.getStatus()!=Status.RUNNING) {
				//移动事件
				staX=startBall.getCenterX();staY=startBall.getCenterY();
				EventHandler<KeyEvent> move=new EventHandler<KeyEvent>() {
					int startX = Integer.valueOf(startPlace[0].trim()),
					startY = Integer.valueOf(startPlace[1].trim());// 将起点坐标数字化
					int len=maze.getHeight();
					MPoint currentPosition=list.get(startX+startY*len);
					double leth = 800 / len;// 获得单位长度
					
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
				//將移動事件添加到startBall中
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
		
		
		// 遍历（广度算法）

		buttonErgodic.setOnAction(e -> {// 遍历按钮
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

				} // list设为true
				for (int i = 0; i < list.size(); i++)
					list.get(i).visted = true;
			}
		});

		// 最短路径
		buFinfShortWay.setOnAction(e -> {// 最短路径按钮
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

		// 初始化
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

		// 返回键
		buttonReturn.setOnAction(e -> {
			stage.close();
			primaryStage.show();
			maze = null;
			list = null;

		});

		// pane.getChildren().add(new Rectangle(100,100,500,500));
		return borderPane;
	}

	// 将迷宫画面画出
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

		// 按照迷宫创建路径创建迷宫图
		timeline = new Timeline(new KeyFrame(Duration.millis(10), ed -> {
			MPoint point = points.remove(0);
			int x = point.getX(), y = point.getY();

			way.addAll((dwlengh / 2 + x * dwlengh), (dhlenth / 2 + y * dhlenth));
			// 每两个点为一个坐标：路径返回时消除结点
			if (way.size() >= 6 && (way.get(way.size() - 2).equals(way.get(way.size() - 6)))
					&& ((way.get(way.size() - 1).equals(way.get(way.size() - 5))))) {
				way.remove(way.size() - 1);
				way.remove(way.size() - 1);
				way.remove(way.size() - 1);
				way.remove(way.size() - 1);

			}
			// 画迷宫
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
			// 迷宫鼠找到终点
			if (points.isEmpty()) {
				timeline.pause();// 动画关闭
				select.setDisable(false);// 选择迷宫大小生成按钮开启
				buttonSet.setDisable(false);// 初始条件按钮开启
			}

		}));

		timeline.setCycleCount(Timeline.INDEFINITE);
		timeline.play();

	}

	/*
	 * 寻路功能 采用右手法制（深度优先）
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
		goway.add(list.get(startX + startY * width));// 按照坐标取出起始位置结点
		// 右手法则 判断方向

		// 建立終末坐標
		Rectangle startRec = new Rectangle(startX * lenth, startY * lenth, lenth, lenth);
		Rectangle endRec = new Rectangle(+endX * lenth, endY * lenth, lenth, lenth);
		startRec.setFill(Color.BLUE);
		endRec.setFill(Color.RED);
		pane.getChildren().addAll(endRec, startBall);

		// 用深度优先寻路
		Polyline line = new Polyline();
		ObservableList<Double> way = line.getPoints();
		line.setStroke(new Color(0, 0, 0, 0));// 记录小球走的所有位置
		while (true) {
			MPoint point = (MPoint) goway.get(top);
			int x = point.getX(), y = point.getY();
			way.addAll((lenth / 2 + x * lenth), (lenth / 2 + y * lenth));
			if (x == endX && y == endY)
				break;
			// 以 右，上，下，左的顺序走
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

		// 记录小球所走路径的最短距离
		Polyline line2 = new Polyline();
		ballWay = new Polyline();// line2,ballWay,均為最短路徑按鈕
		ObservableList<Double> wayPoint = line2.getPoints();
		ObservableList<Double> wayPointball = ballWay.getPoints();
		for (int i = 0; i < goway.size(); i++) {
			double x = goway.get(i).getX(), y = goway.get(i).getY();
			wayPoint.addAll((lenth / 2 * 0.8 + x * lenth), (lenth / 2 * 0.8 + y * lenth));
			wayPointball.addAll((lenth / 2 * 0.8 + x * lenth), (lenth / 2 * 0.8 + y * lenth));
		}

		for (int i = 0; i < list.size(); i++)
			list.get(i).visted = true;

		// 單步尋路
		/*
		 * 走一步，便在那画一小球
		 * 
		 * 
		 */
		singleWay.setDisable(false);
		ArrayList<Circle> tested = new ArrayList<>();
		singleWay.setOnAction(e -> {

			// 不能遍历
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
					System.out.println("路径已显示");
				}
			}

		});

		// 创建小球行驶动画
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
		// 开始，暂停按钮
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
	 * 实现初始化功能。将矩形框里的内容覆盖
	 * 
	 * 
	 * 即再覆蓋一成
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
			this.width = 4; // 迷宫宽度
			this.height = 4; // 迷宫高度
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

		// 深度优先创建迷宫
		private ArrayList<MPoint> CreateMaze(ArrayList<MPoint> maze) {
			int x = 0;
			int y = 0;
			ArrayList<MPoint> sweap = new ArrayList<MPoint>();
			startlist = new ArrayList<MPoint>();
			sweap.add(maze.get(x + y * width));
			while (!sweap.isEmpty()) {
				boolean flag = false;
				MPoint pt = (MPoint) sweap.get(sweap.size() - 1);// 取出末尾元素
				startlist.add(pt);
				x = pt.getX();
				y = pt.getY();
				pt.visted = true;
				// 添加四个方向的数值化值
				Stack<Integer> dir = new Stack<>();
				dir.add(0);// 左边
				dir.add(1);// 右边
				dir.add(2); // 上边
				dir.add(3);// 下边
				// 四个方向都不能走,结束循环
				while (!dir.isEmpty()) {
					int sel = (int) (Math.random() * dir.size());// 随机选择方向
					switch (dir.get(sel)) {
					case 0: // 左边
						if ((x - 1) >= 0 && maze.get(x - 1 + y * width).visted == false) {
							maze.get(x + y * width).setLeft();
							maze.get(x - 1 + y * width).setRight();
							sweap.add(maze.get(x - 1 + y * width));
							flag = true;

						}
						break;
					case 1: // 右边
						if ((x + 1) < width && maze.get(x + 1 + y * width).visted == false) {

							maze.get(x + y * width).setRight();// 设为0，注：0表示为通路
							maze.get(x + 1 + y * width).setLeft();
							sweap.add(maze.get(x + 1 + y * width));
							flag = true;
						}
						break;
					case 2: // 上边
						if ((y - 1) >= 0 && maze.get(x + (y - 1) * width).visted == false) {
							maze.get(x + y * width).setUp();
							maze.get(x + (y - 1) * width).setDown();
							sweap.add(maze.get(x + (y - 1) * width));
							flag = true;
						}
						break;
					case 3: // 下边
						if ((y + 1) < height && maze.get(x + (y + 1) * width).visted == false) {
							maze.get(x + y * width).setDown();
							maze.get(x + (y + 1) * width).setUp();
							sweap.add(maze.get(x + (y + 1) * width));
							flag = true;
						}
						break;
					}
					if (flag)// 判断选择的方向是否可走
						break;
					dir.remove(sel);// 没有则移除该选择方向
				}
				if (!flag) {// 四个方向都不可走
					sweap.remove(sweap.size() - 1);
					/*
					 * 
					 * 
					 * 
					 * 避免只出现一条通往终点的路
					 */
					// 选择一方向突破
					if ((int) (Math.random() * 10) == 0)// 1/10的可能 突破
						switch ((int) (Math.random() * 4)) {
						case 0: // 左边
							if ((x - 1) >= 0) {
								maze.get(x + y * width).setLeft();
								maze.get(x - 1 + y * width).setRight();

							}
							break;
						case 1: // 右边
							if ((x + 1) < width) {

								maze.get(x + y * width).setRight();// 设为0，注：0表示为通路
								maze.get(x + 1 + y * width).setLeft();

							}
							break;
						case 2: // 上边
							if ((y - 1) >= 0) {
								maze.get(x + y * width).setUp();
								maze.get(x + (y - 1) * width).setDown();

							}
							break;
						case 3: // 下边
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
			 * 记录迷宫
			 */
			PrintWriter writer = null;
			try {
				writer = new PrintWriter("H:\\JAVA\\11703990535\\迷宫\\迷宫地图\\" + height + "_" + width + ".txt");
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
