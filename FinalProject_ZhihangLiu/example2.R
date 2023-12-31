# Load required libraries
library(ggplot2)

# Read data from the text file
data <- read.table("graph.txt", header = FALSE)

# Assign column names
colnames(data) <- c("Column1", "Timestamp")

# Convert Timestamp column to POSIXct format
data$Timestamp <- as.POSIXct(data$Timestamp, format = "%Y-%m-%d-%H:%M:%S")

# Plotting Column1 data versus Timestamp
myplot <- ggplot(data, aes(x = Timestamp, y = Column1)) +
  geom_line() +
  geom_point() +  # Plotting points
  labs(x = "Time", y = "Portfolio value", title = "Portfolio value change")

print(myplot)