package stock;

import org.eclipse.jetty.server.Server;
import org.eclipse.jetty.servlet.ServletContextHandler;
import org.eclipse.jetty.servlet.ServletHolder;

import org.eclipse.jetty.server.Server;
import org.eclipse.jetty.servlet.ServletContextHandler;
import org.eclipse.jetty.servlet.ServletHolder;

import com.sun.jersey.spi.container.servlet.ServletContainer;

public class JettyServer {

	public static void main(String[] args) throws Exception {

		ServletHolder sh = new ServletHolder(ServletContainer.class);
		sh.setInitParameter("com.sun.jersey.config.property.resourceConfigClass",
				"com.sun.jersey.api.core.PackagesResourceConfig");
		sh.setInitParameter("com.sun.jersey.config.property.packages", "stock");
		sh.setInitParameter("com.sun.jersey.api.json.POJOMappingFeature", "true");

		Server server = new Server(9090);
		ServletContextHandler context = new ServletContextHandler(server, "/", ServletContextHandler.SESSIONS);
		context.addServlet(sh, "/*");
		server.start();
		server.join();

	}
}