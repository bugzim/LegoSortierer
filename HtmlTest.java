import com.fazecast.jSerialComm.SerialPort;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.Statement;
import java.sql.SQLException;
import java.sql.ResultSet;
import static spark.Spark.*;
import com.google.gson.Gson;
import java.util.List;
import java.util.ArrayList;
import java.util.Map;
import java.util.HashMap;

public class HtmlTest { 
	
	public static void main (String[] args) {
		
		
		
		port(8080);
		get("api/farben", (req, res) -> {
			res.type("application/json");
			
			List<Map<String, Integer>> farbenListe = new ArrayList<>();
			
			var url = "jdbc:sqlite:/home/robinnordhausen/ArduinoSerialReader/legoStorage.db";

		try (Connection conn = DriverManager.getConnection(url)) {		
			 Statement stmt = conn.createStatement();
             ResultSet rs = stmt.executeQuery("SELECT * FROM farben");
             
             while (rs.next()) {
				 Map<String, Integer> f = new HashMap<>();
				 f.put("r", rs.getInt("r"));
				 f.put("g", rs.getInt("g"));
				 f.put("b", rs.getInt("b"));
				 f.put("c", rs.getInt("c"));
				 f.put("y", rs.getInt("y"));
				 f.put("m", rs.getInt("m"));
				 f.put("w", rs.getInt("w"));
				 farbenListe.add(f);
			 }
			 
			 rs.close();
			 stmt.close();
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }   
        
			return new Gson().toJson(farbenListe);
		});
	
		}
	}
