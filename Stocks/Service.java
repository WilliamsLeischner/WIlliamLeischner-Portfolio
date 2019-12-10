package stock;

import java.io.InputStream;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import javax.ws.rs.Consumes;
import javax.ws.rs.GET;
import javax.ws.rs.POST;
import javax.ws.rs.PUT;
import javax.ws.rs.Path;
import javax.ws.rs.PathParam;
import javax.ws.rs.Produces;
import javax.ws.rs.core.MediaType;

import com.mongodb.client.AggregateIterable;
import com.mongodb.client.FindIterable;
import com.mongodb.client.MongoCollection;
import com.mongodb.client.MongoDatabase;
import com.mongodb.BasicDBObject;
import com.mongodb.DBObject;
import com.mongodb.MongoClient;

import org.bson.Document;
import org.bson.conversions.Bson;
import org.bson.types.ObjectId;
import com.mongodb.client.model.Filters;
import com.mongodb.client.model.Updates;
import com.mongodb.util.JSON;

@Path("")
public class Service {

	MongoClient mongo = new MongoClient("localhost", 27017);
	MongoDatabase database = mongo.getDatabase("market");
	MongoCollection<Document> collection = database.getCollection("stocks");

	@POST
	@Path("/createStock/{ticket}")
	@Produces(MediaType.TEXT_PLAIN)
	@Consumes(MediaType.APPLICATION_JSON)
	public String createStock(@PathParam("ticket") String ticket, InputStream is) {
		System.out.println(ticket);
		try {
			String json = new String(is.readAllBytes());
			Document document = Document.parse(json);
			if (document.containsKey("Ticker")) {
				document.remove("Ticker");
			}

			document.put("Ticker", ticket);
			for (String key : document.keySet()) {
				System.out.println(document.get(key));
			}
			collection.insertOne(document);

			BasicDBObject query = new BasicDBObject();
			query.put("_id", document.getObjectId("_id").toString());

			FindIterable<Document> documents = collection.find(query);
			FindIterable<Document> docs = collection.find(); // SELECT * FROM sample;
			for (Document doc : docs) {
				return "Created Document \n " + doc.toJson() + "\n\n ";// #return inserted document.
			}

		} catch (Exception ex) {
			ex.printStackTrace();
		}
		return "ERROR";
	}

	@PUT
	@Path("/updateStock/{ticket}")
	@Produces(MediaType.TEXT_PLAIN)
	@Consumes(MediaType.APPLICATION_JSON)
	public String updateStock(@PathParam("ticket") String ticket, InputStream is) {
		System.out.println(ticket);
		try {
			String json = new String(is.readAllBytes());
			Document document = Document.parse(json);
			if (document.containsKey("Ticker")) {
				document.remove("Ticker");
			}
			document.put("Ticker", ticket);

			BasicDBObject query = new BasicDBObject();
			query.put("Ticker", ticket);

			FindIterable<Document> documents = collection.find(query);
			Document update_document = null;
			for (Document doc : documents) {
				update_document = doc;
				break;
			}
			if (update_document == null) {
				return "NOTFOUND";
			}
			BasicDBObject updateFields = new BasicDBObject();

			for (String key : document.keySet()) {
				updateFields.append(key, document.get(key));
			}
			BasicDBObject setQuery = new BasicDBObject();
			setQuery.append("$set", updateFields);

			BasicDBObject searchQuery = new BasicDBObject("_id", update_document.getObjectId("_id").toString());

			collection.updateOne(searchQuery, setQuery);
			documents = collection.find(query);
			update_document = null;
			for (Document doc : documents) {
				update_document = doc;
				break;
			}
			if (update_document != null) {
				return "\nUpdated Values\n" + update_document.toJson() + "\n";
			}

		} catch (Exception ex) {
			ex.printStackTrace();
		}
		return "ERROR";
	}

	@GET
	@Path("/getStock/{ticket}")
	@Produces(MediaType.TEXT_PLAIN)
	@Consumes(MediaType.APPLICATION_JSON)
	public String getStock(@PathParam("ticket") String ticket) {
		System.out.println(ticket);
		try {
			BasicDBObject query = new BasicDBObject();
			query.put("Ticker", ticket);

			FindIterable<Document> documents = collection.find(query);
			Document update_document = null;
			for (Document doc : documents) {
				update_document = doc;
				break;
			}
			if (update_document == null) {
				return "NOTFOUND";
			}

			return update_document.toJson();

		} catch (Exception ex) {
			ex.printStackTrace();
		}
		return "ERROR";
	}

	@GET
	@Path("/deleteStock/{ticket}")
	@Produces(MediaType.TEXT_PLAIN)
	@Consumes(MediaType.APPLICATION_JSON)
	public String deleteStock(@PathParam("ticket") String ticket) {
		System.out.println(ticket);
		try {
			BasicDBObject query = new BasicDBObject();
			query.put("Ticker", ticket);

			FindIterable<Document> documents = collection.find(query);
			Document update_document = null;
			for (Document doc : documents) {
				update_document = doc;
				break;
			}
			if (update_document == null) {
				return "NOTFOUND";
			}
			collection.deleteMany(query);
			return "Document with Ticker " + ticket + " Has been deleted from the stocks Collection";

		} catch (Exception ex) {
			ex.printStackTrace();
		}
		return "ERROR";
	}

	@POST
	@Path("/stockReport")
	@Produces(MediaType.APPLICATION_JSON)
	@Consumes(MediaType.APPLICATION_JSON)
	public List<String> create_stockReport(InputStream is) {
		List<String> fields = new ArrayList<String>();
		try {
			String json = new String(is.readAllBytes());
			Document document = Document.parse(json);
			String myList = document.getString("list");
			myList = myList.replace("[", "");
			myList = myList.replace("]", "");
			String[] items = myList.split(",");

			for (String ticker : items) {
				String field = getReport(ticker);
				fields.add(field);
			}
			System.out.println(myList);
		} catch (Exception ex) {
			ex.printStackTrace();
		}
		return fields;
	}

	@GET
	@Path("/industryReport/{industry}")
	@Produces(MediaType.TEXT_PLAIN)
	@Consumes(MediaType.APPLICATION_JSON)
	public String create_industryReport(@PathParam("industry") String industry) {
		industry = industry.replace("_", " ");// #removes underscore form the string
		System.out.println(industry);
		try {
			Document included_Values = new Document("$project", new Document("Industry", 1)
					.append("Performance (YTD)", 1).append("Performance (Week)", 1).append("Volume", 1));
			Document document_Type = new Document("$match", new Document("Industry", industry));
			Document grouped_Summery_Data = new Document("$group",
					new Document("_id", "$Industry")
							.append("Average Performance (YTD)", new Document("$avg", "$Performance (YTD)"))
							.append("Average Performance (Week)", new Document("$avg", "$Performance (YTD)"))
							.append("Total Volume", new Document("$sum", "$Volume")));

			Document items_Limit = new Document("$limit", 5);

			AggregateIterable<Document> output = collection
					.aggregate(Arrays.asList(included_Values, document_Type, grouped_Summery_Data, items_Limit));

			return "\n Portfolio Report For The First Five " + industry + " Industries \n\n " + JSON.serialize(output)
					+ " \n";

		} catch (Exception ex) {
			ex.printStackTrace();
		}
		return "ERROR";
	}

	@GET
	@Path("/portfolio/{company}")
	@Produces(MediaType.TEXT_PLAIN)
	@Consumes(MediaType.APPLICATION_JSON)
	public String create_portfolio(@PathParam("company") String company) {
		company = company.replace("_", " "); // #removes underscore form the string
		System.out.println(company);
		try {
			BasicDBObject query = new BasicDBObject();
			query.put("Company", company);
			FindIterable<Document> documents = collection.find(query);
			return "\n Portfolio Report For " + company + " Company \n\n " + JSON.serialize(documents) + " \n";

		} catch (Exception ex) {
			ex.printStackTrace();
		}
		return "ERROR";
	}

	public String getReport(String ticker) {
		Document included_Values = new Document("$project", new Document("Ticker", 1).append("Performance (YTD)", 1)
				.append("Performance (Week)", 1).append("Shares Outstanding", 1).append("Volume", 1));
		Document document_Type = new Document("$match", new Document("Ticker", ticker));
		Document grouped_Summery_Data = new Document("$group",
				new Document("_id", "$Ticker")
						.append("Average Performance (YTD)", new Document("$avg", "$Performance (YTD)"))
						.append("Average Performance (Week)", new Document("$avg", "$Performance (YTD)"))
						.append("Total Volume", new Document("$sum", "$Volume")));

		AggregateIterable<Document> output = collection
				.aggregate(Arrays.asList(included_Values, document_Type, grouped_Summery_Data));

		return JSON.serialize(output);
	}
}
